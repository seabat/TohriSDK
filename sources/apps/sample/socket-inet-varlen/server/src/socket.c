#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "command.h"
#include "socket.h"

static void* receive_thread( thread_arg_st* arg ){
	int            in_header_size = 0;
	char outBuf[BUFFER_SIZE] = { '\0' };
	int  recv_len       =0;
	int  send_len       =0;
	int  res_flg = 0; /* 1:response is present, 0:response is none */ 

	printf( "START receive_thread() [FD=%d]\n", arg->acceptFD );

	in_header_size = sizeof(arg->cmd_id) + sizeof(arg->cmd_in_size);

	memset( &arg->cmd_id, 0, in_header_size );

	/* Receive com_id */
	printf( "6: wait message [FD=%d]\n", arg->acceptFD );
	if( 0>(recv_len=recv(arg->acceptFD, &arg->cmd_id, sizeof(arg->cmd_id), 0)) ){
		perror("recv");
		goto error;	
	}

	printf( "command id=%d\n", arg->cmd_id );

	/* Receive comd_in_size */
	if( 0>(recv_len=recv(arg->acceptFD, arg->cmd_in_size, sizeof(arg->cmd_in_size), 0)) ){
		perror("recv");
		goto error;	
	}

	printf( "com_id=%d com_payload_size=%d [FD=%d]\n", 
			arg->cmd_id, 
			(arg->cmd_in_size[3]) | (arg->cmd_in_size[2]<<8) | (arg->cmd_in_size[1]<<16) | (arg->cmd_in_size[0]<<24),
			arg->acceptFD );

	res_flg=dispatch_command( arg );

error:
	close(arg->acceptFD);
	arg->status = 1;

	/* If allocated memory in a main thread is used in a sub thread, */
	/* the memory should be freed in the sub thread.                 */
	if(NULL!=arg) free(arg);
	printf( "END receive_thread()\n" );

	pthread_exit( NULL );
}

static void create_receive_thread(int acceptFD)                                                                     
{
	int 		   res = 0;
	pthread_t      thread_id;
	thread_arg_st* p_thread_arg;
	pthread_attr_t attr;

	printf( "START create_receive_thread() [FD=%d]\n", acceptFD );

	p_thread_arg = (thread_arg_st*)malloc(sizeof(thread_arg_st));
	p_thread_arg->acceptFD = acceptFD;

	/* If allocated memory in a main thread is used in a sub thread, the memory should be freed in the sub thread. */
	/* Otherwise the memory may be freed in the main  before the memory is used in the sub. */
	pthread_attr_init(&attr);                                                                                                                                                                                      
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	res = pthread_create(&thread_id, &attr, (void*)receive_thread, p_thread_arg );
	if(0!=res) fprintf( stderr, "pthread_create : %s", strerror( res ) ); 

	printf("5: main thread continues to run\n");

	printf("END create_receive_thread()\n");
	return;
}


int socket_main(char* ipaddr, int port)
{
	int  socketFD      = -1;
	int  acceptFD      = -1;
	int  sockaddr_size = 0;
	struct sockaddr_in srv_socket_addr;
	struct sockaddr_in clt_socket_addr;
	socklen_t          sin_size;

	if( NULL==ipaddr ){
		goto error;
	}

	/* socket  */
	socketFD = socket(PF_INET,     /* IPv4              */
					SOCK_STREAM,   /* for TCP           */
					0);            /* internet protocol */
	if( socketFD<0 ){
		perror("socket");
		goto error;
	}

	bzero((void*)&srv_socket_addr, sizeof(srv_socket_addr)); /* This step is very important. */

	/* bind */
	srv_socket_addr.sin_family = PF_INET;							/* sin_family */
	if( 0==strncmp(ipaddr,"0.0.0.0", 16) ){
		srv_socket_addr.sin_addr.s_addr   = htonl( INADDR_ANY );	/* sin_addr   */
	}else{
		inet_aton( ipaddr, &(srv_socket_addr.sin_addr) );			/* sin_addr   */
	}
	srv_socket_addr.sin_port   = htons( (unsigned short)port );		/* sin_port   */

	printf( "1: IP=%s PORT=%d\n", inet_ntoa(srv_socket_addr.sin_addr), srv_socket_addr.sin_port );

	sockaddr_size = sizeof(struct sockaddr_in);
	if( bind(socketFD, (struct sockaddr *)&srv_socket_addr, sockaddr_size) < 0){
		perror("bind");
		goto exit;
	}

	/* listen */
	if(listen(socketFD, SOMAXCONN) < 0 ){
		perror("listen");
		goto exit;
	}

	printf("2: SOCKET FD=%d\n",socketFD);

	while(1){
		/* accpet  */
		printf("3: wait in accept\n");
		if((acceptFD = accept(socketFD, (struct sockaddr *)&clt_socket_addr, &sin_size)) < 0){
			perror("accept");
			goto exit;
		}

		/* accept()でwaitしていなくてもlisten()で指定したキュー数の接続は捕捉できる。       */
		/*                                                                                  */
		/* より多くのクライアントとコネクションを確立したい場合は以下の２つを実施する。     */
		/* 1. コネクション確立後の処理をthred化する。                                       */
		/* 2. コネクション確立待ちをaccept()ではなくselect()にする。                        */

		printf( "4: accept FD=%d  connect from %s : %u\n", 
				acceptFD,
				inet_ntoa(clt_socket_addr.sin_addr), 
				ntohs(clt_socket_addr.sin_port) );

		create_receive_thread(acceptFD);
	}

exit:
	if( -1!=socketFD ){
		close(socketFD);
	}
	return 0;
error:
	return -1;
}
