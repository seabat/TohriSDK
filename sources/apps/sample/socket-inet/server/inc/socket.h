
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
 * socket$B;XDjJ}K!$O#3$D(B
 *   1. any address
 *   $B%M%C%H%o!<%/%+!<%I$K3d$jEv$F$i$l$?A4(BIP$B%"%I%l%9$r;HMQ$9$k>l9g(B
 *   #if defined(FEATURE_SOCKET_ANY_ADDRESS)
 *	 struct sockaddr_in srv_socket_addr;
 *	 srv_socket_addr.sin_port        = htons( (unsigned short)10000 );
 *   srv_socket_addr.sin_addr.s_addr = htonl( INADDR_ANY );
 *   #endif
 *
 *   $B%"%I%l%9(B=INADDR_ANY,$B%]!<%H(B=0 $B$NAH$_9g$o$;$O%/%i%$%"%s%H$H%3%M%/%7%g%s$N3NN)(B
 *   $B$,$G$-$J$$!#%"%I%l%9(B=INADDR_ANY$B$N>l9g$b%]!<%H$r;XDj$9$k$3$H(B

 *   2. specific address
 *   $B%M%C%H%o!<%/%+!<%I$K3d$jEv$F$i$l$?FCDj$N(BIP$B%"%I%l%9$r;HMQ$9$k>l9g(B
 *   #if defined(FEATURE_SOCKET_ONE_ADDRESS)
 *	 struct sockaddr_in srv_socket_addr;
 *	 srv_socket_addr.sin_port   = htons( (unsigned short)10000 );
 *	 inet_aton( "192.168.41.2", &(srv_socket_addr.sin_addr) );
 *   #endif
 *   
 *   3. loopback address
 *   $B%k!<%W%P%C%/%"%I%l%9$r;HMQ$9$k>l9g(B
 *   #if defined(FEATURE_SOCKET_NO_ADDRESS)
 *	 struct sockaddr_in srv_socket_addr;
 *	 srv_socket_addr.sin_port   = htons( (unsigned short)10000 );
 *	 inet_aton( "127.0.0.1", &(srv_socket_addr.sin_addr) );
 *   #enfif
 *
 *   $B%5!<%P!<$N(Bbind()$B$N%"%I%l%9$K(B"127.0.0.1"$B$r;XDj$7!"%/%i%$%"%s%H$N(Bconnect()$B$K(B
 *   "127.0.0.1"$B$r;XDj$9$k!#$5$i$KN><B9T%U%!%$%k$rF1(BPC$BFb$KCV$$$F%3%M%/%7%g%s$r3NN)(B
 *   $B$G$-$k(B
 */


int socket_main(char* ipaddr, int port);

