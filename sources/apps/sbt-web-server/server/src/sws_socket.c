#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "libsbt/sbt_log.h"
#include "sws_command.h"
#include "sws_socket.h"

static void* receive_thread( thread_arg_st* arg ){
//	int            in_header_size = 0;
//	char outBuf[BUFFER_SIZE] = { '\0' };
	int  recv_len       = 0;
//	int  send_len       = 0;
	int  res_flg        = 0; /* 1:response is present, 0:response is none */ 
	pthread_t tid       = pthread_self();

	LOGD( "[TID=%p][FD=%d]START", tid, arg->acceptFD );

	/* Initialize arg */
	arg->http_req_size = HTTP_REQ_SIZE;
	LOGD( "[TID=%p][FD=%d]Wait message", tid, arg->acceptFD );
	if( 0>(recv_len=recv(arg->acceptFD, arg->http_req_data, arg->http_req_size, 0)) ){
		perror("recv");
		goto error;	
	}
	LOGD( "[TID=%p][FD=%d]receive size=%d", tid, arg->acceptFD, recv_len );

	res_flg=sws_dispatch_command( arg );

error:
	LOGD( "[TID=%p][FD=%d]Close socket", tid, arg->acceptFD );
	close(arg->acceptFD);
	arg->status = 1;

	/* If allocated memory in a main thread is used in a sub thread, */
	/* the memory should be freed in the sub thread.                 */
	if(NULL!=arg) free(arg);
	LOGD( "[TID=%p]END", tid );

	pthread_exit( NULL );
}

static void create_receive_thread(int acceptFD)
{
	int 		   res = 0;
	pthread_t      thread_id;
	thread_arg_st* p_thread_arg;
	pthread_attr_t attr;

	LOGD( "START create_receive_thread() [FD=%d]", acceptFD );

	p_thread_arg = (thread_arg_st*)malloc(sizeof(thread_arg_st));
	p_thread_arg->acceptFD = acceptFD;

	/* If allocated memory in a main thread is used in a sub thread, the memory should be freed in the sub thread. */
	/* Otherwise the memory may be freed in the main  before the memory is used in the sub. */
	pthread_attr_init(&attr);                                                                                                                                                                                      
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	res = pthread_create(&thread_id, &attr, (void*)receive_thread, p_thread_arg );
	if(0!=res) LOGD( "pthread_create : %s", strerror( res ) ); 

	LOGD("5: main thread continues to run");

	LOGD("END create_receive_thread()");
	return;
}


int sws_socket_main(char* ipaddr, int port)
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

	LOGD( "1: IP=%s PORT=%d", inet_ntoa(srv_socket_addr.sin_addr), srv_socket_addr.sin_port );

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

	LOGD("2: SOCKET FD=%d",socketFD);

	while(1){
		/* accpet  */
		LOGD("3: wait in accept");
		if((acceptFD = accept(socketFD, (struct sockaddr *)&clt_socket_addr, &sin_size)) < 0){
			perror("accept");
			goto exit;
		}

		/* accept()でwaitしていなくてもlisten()で指定したキュー数の接続は捕捉できる。       */
		/*                                                                                  */
		/* より多くのクライアントとコネクションを確立したい場合は以下の２つを実施する。     */
		/* 1. コネクション確立後の処理をthred化する。                                       */
		/* 2. コネクション確立待ちをaccept()ではなくselect()にする。                        */

		LOGD( "4: accept FD=%d  connect from %s : %u", 
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
