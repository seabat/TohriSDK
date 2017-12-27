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

#if !defined(FEATURE_THREAD_DETATCH) && \
    !defined(FEATURE_THREAD_JOIN) && \
    !defined(FEATURE_THREAD_NONE)
	#error
#endif

typedef struct thread_arg{
	int  acceptFD;
	char cmd_res_data[BUFFER_SIZE];
	int  status;
}thread_arg_st;

static void* receive_thread( thread_arg_st* arg ){
	char inBuf[BUFFER_SIZE] =  { '\0' };
	char outBuf[BUFFER_SIZE] = { '\0' };
	int  recv_len  = 0;
	int  send_len  = 0;
	int  res_flg   = 0; /* 1:response is present, 0:response is none */ 
	pthread_t tid  = pthread_self();

	printf( "[TID=%p]START %s [FD=%d]\n", tid, __FUNCTION__, arg->acceptFD );

	while( strncmp(inBuf, "EXIT\r\n", 6) != 0 && strncmp(inBuf, "EXIT\n", 5) != 0 ){
		memset( inBuf, 0, BUFFER_SIZE );
		/* receive */
		printf( "[TID=%p]6: wait message [FD=%d]\n", tid, arg->acceptFD );
		if( 0>(recv_len=recv(arg->acceptFD, inBuf, BUFFER_SIZE, 0)) ){
			perror("recv");
			break;	
		}

		inBuf[recv_len] = '\0';
		printf( "[TID=%p][FD=%d] -> %s \n", tid, arg->acceptFD , inBuf);

		res_flg=dispatch_command( inBuf, outBuf );
		memcpy( arg->cmd_res_data, outBuf, BUFFER_SIZE );

		/* send */
		if(1==res_flg){
			send_len = send( arg->acceptFD, inBuf, recv_len, 0 );
		}
	}

	printf( "[TID=%p]7: close FD [FD=%d]\n", tid, arg->acceptFD );
	close(arg->acceptFD);
	arg->status = 1;

#if defined(FEATURE_THREAD_DETATCH)
	/* If allocated memory in a main thread is used in a sub thread, */
	/* the memory should be freed in the sub thread.                 */
	if(NULL!=arg) free(arg);
#endif
	printf( "[TID=%p]END %s\n", tid, __FUNCTION__ );

	pthread_exit( NULL );
}

static void create_receive_thread(int acceptFD)                                                                     
{
#if defined(FEATURE_THREAD_JOIN) || defined(FEATURE_THREAD_DETATCH)
	int 		   res = 0;
	pthread_t      thread_id;
	thread_arg_st* p_thread_arg;
#endif
#if defined(FEATURE_THREAD_DETATCH)
	pthread_attr_t attr;
#endif

	printf( "START %s [FD=%d]\n", __FUNCTION__, acceptFD );

	p_thread_arg = (thread_arg_st*)malloc(sizeof(thread_arg_st));
	p_thread_arg->acceptFD = acceptFD;

#if defined (FEATURE_THREAD_JOIN)
	res = pthread_create( &thread_id, NULL, (void*)receive_thread, p_thread_arg );
	if(0!=res) fprintf( stderr, "pthread_create : %s", strerror( res ) ); 

	printf( "5: pause main thread\n" );
	pthread_join( thread_id, NULL );
	printf( "resume main thread return=%s status=%d\n", p_thread_arg->cmd_res_data, p_thread_arg->status );
	if(NULL!=p_thread_arg) free(p_thread_arg);

#elif defined(FEATURE_THREAD_DETATCH)
	/* If allocated memory in a main thread is used in a sub thread, the memory should be freed in the sub thread. */
	/* Otherwise the memory may be freed in the main  before the memory is used in the sub. */
	pthread_attr_init(&attr);                                                                                                                                                                                      
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	res = pthread_create(&thread_id, &attr, (void*)receive_thread, p_thread_arg );
	if(0!=res) fprintf( stderr, "pthread_create : %s", strerror( res ) ); 

	printf("5: main thread continues to run\n");

#elif defined(FEATURE_THREAD_NONE)
	receive_thread(p_thread_arg);
#endif

	printf("END %s\n", __FUNCTION__);
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
