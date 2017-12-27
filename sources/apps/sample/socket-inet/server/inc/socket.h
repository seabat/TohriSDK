
#define DBG            1

/* select feature of thread  */
//#define FEATURE_THREAD_DETATCH
//#define FEATURE_THREAD_JOIN
//#define FEATURE_THREAD_NONE

/* select feature of socket's address */
//#define FEATURE_SOCKET_ANY_ADDRESS
//#define FEATURE_SOCKET_ONE_ADDRESS
//#define FEATURE_SOCKET_NO_ADDRESS

/*
 * socket指定方法は３つ
 *   1. any address
 *   ネットワークカードに割り当てられた全IPアドレスを使用する場合
 *   #if defined(FEATURE_SOCKET_ANY_ADDRESS)
 *	 struct sockaddr_in srv_socket_addr;
 *	 srv_socket_addr.sin_port        = htons( (unsigned short)10000 );
 *   srv_socket_addr.sin_addr.s_addr = htonl( INADDR_ANY );
 *   #endif
 *
 *   アドレス=INADDR_ANY,ポート=0 の組み合わせはクライアントとコネクションの確立
 *   ができない。アドレス=INADDR_ANYの場合もポートを指定すること

 *   2. specific address
 *   ネットワークカードに割り当てられた特定のIPアドレスを使用する場合
 *   #if defined(FEATURE_SOCKET_ONE_ADDRESS)
 *	 struct sockaddr_in srv_socket_addr;
 *	 srv_socket_addr.sin_port   = htons( (unsigned short)10000 );
 *	 inet_aton( "192.168.41.2", &(srv_socket_addr.sin_addr) );
 *   #endif
 *   
 *   3. loopback address
 *   ループバックアドレスを使用する場合
 *   #if defined(FEATURE_SOCKET_NO_ADDRESS)
 *	 struct sockaddr_in srv_socket_addr;
 *	 srv_socket_addr.sin_port   = htons( (unsigned short)10000 );
 *	 inet_aton( "127.0.0.1", &(srv_socket_addr.sin_addr) );
 *   #enfif
 *
 *   サーバーのbind()のアドレスに"127.0.0.1"を指定し、クライアントのconnect()に
 *   "127.0.0.1"を指定する。さらに両実行ファイルを同PC内に置いてコネクションを確立
 *   できる
 */


int socket_main(char* ipaddr, int port);

