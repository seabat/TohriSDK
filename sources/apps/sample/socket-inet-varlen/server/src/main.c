#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "socket.h"

/* set server address */
#define SERVER_ADDRESS "192.168.11.2" /* chahge your server's ip address */
#define SERVER_PORT    10000          /* change your port  */

#define LOCAL_ADDRESS  "127.0.0.1"
#define ANY_ADDRESS    "0.0.0.0"

#if !defined(FEATURE_SOCKET_ONE_ADDRESS) && \
    !defined(FEATURE_SOCKET_NO_ADDRESS) && \
    !defined(FEATURE_SOCKET_ANY_ADDRESS)
	#error
#endif

int main(int argc, char **argv)
{
	char            ipaddr[16] = {0};
	unsigned short  port       = 0;

	if( 3>argc ){
#if defined(FEATURE_SOCKET_ONE_ADDRESS)
		strncpy(ipaddr, SERVER_ADDRESS,16);
#elif defined(FEATURE_SOCKET_NO_ADDRESS)
		strncpy(ipaddr, LOCAL_ADDRESS, 16);
#elif defined(FEATURE_SOCKET_ANY_ADDRESS)
		strncpy(ipaddr, ANY_ADDRESS,   16);
#endif
		port = SERVER_PORT;
	}else{
		if(argv[1]){
			printf("argv[1]=%s\n", argv[1]);
			strncpy(ipaddr, argv[1] ,16);
		}

		if(argv[2]){
			printf("argv[2]=%s\n", argv[2]);
			port=(unsigned short)atoi(argv[2]);
		}
	}

	printf( "ipaddr=%s port=%d\n", ipaddr, port );

	socket_main(ipaddr, port);
	return 0;
}
