#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define FEATURE_REMOTE_SERVER_ADDRESS

#define DBG            1
#define BUFFER_SIZE    256
#define SERVER_ADDRESS "192.168.11.2"
#define LOCAL_ADDRESS  "128.0.0.1"
#define ANY_ADDRESS    "0.0.0.0"
#define SERVER_PORT    10000
#if !defined(FEATURE_SOCKET_ONE_ADDRESS) && \
    !defined(FEATURE_SOCKET_NO_ADDRESS) && \
    !defined(FEATURE_SOCKET_ANY_ADDRESS)
	#error
#endif

void sbt_dump( const unsigned char* buf, int start_index, int end_index ){

	int i          = 0;
    int dump_size  = 0;
	unsigned char* dump_buf = NULL;

	dump_size = end_index - start_index + 1;
	dump_size+= 16 - dump_size%16;
	dump_buf  = (unsigned char*)malloc( dump_size );
	memset( dump_buf, 0x00, dump_size );
	memcpy( dump_buf, buf+start_index, end_index - start_index + 1 );

	fprintf(stderr,     "+0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
	for(i=0; i+16<=dump_size; i+=16){ 
		fprintf(stderr, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
				dump_buf[i+ 0],
				dump_buf[i+ 1],
				dump_buf[i+ 2],
				dump_buf[i+ 3],
				dump_buf[i+ 4],
				dump_buf[i+ 5],
				dump_buf[i+ 6],
				dump_buf[i+ 7],
				dump_buf[i+ 8],
				dump_buf[i+ 9],
				dump_buf[i+10],
				dump_buf[i+11],
				dump_buf[i+12],
				dump_buf[i+13],
				dump_buf[i+14],
				dump_buf[i+15]
		);
	}
	
	free(dump_buf);
}


static void send_and_recv(int socketFD){
	int stdin_len = 0;
	int send_len  = 0;
	int recv_len  = 0;

	char inBuf[BUFFER_SIZE] = { '\0' };
	char outBuf[] = { 0x02, 
					  0x00, 0x00, 0x00, 0x12, 
					  0x31, 0x32, 0x33, 0x34,0x35, 0x36, 0x37, 0x38,0x39, 0x40, 0x41, 0x42,0x43, 0x44, 0x45, 0x46, 
					  0x47, 0x00 };

	/* send */
//	do{
//		memset(inBuf, '\0', sizeof(inBuf));
//		memset(outBuf,'\0', sizeof(outBuf));

//		printf("Enter send message:\n");
//		fgets(outBuf,BUFFER_SIZE, stdin);
		stdin_len = strlen(outBuf);

		printf("<-- %s\n", outBuf);
		sbt_dump( outBuf, 0, sizeof(outBuf)-1 );

		send_len  = send(socketFD, outBuf, sizeof(outBuf), 0);
		recv_len  = recv(socketFD, inBuf,  sizeof(inBuf),  0);
		printf("--> %s\n", inBuf);
//	}while(strncmp(inBuf, "EXIT\r\n", 6) != 0 && strncmp(inBuf, "EXIT\n", 5) != 0);

}

int main(int argc, char **argv)
{
	int  socketFD;
	int  sockaddr_size;
	struct sockaddr_in srv_socket_addr;

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

	/* socket  */
	socketFD = socket(PF_INET, SOCK_STREAM, 0);
	if( socketFD < 0 ){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* bind */
	srv_socket_addr.sin_family = PF_INET;								/* sin_family */
	if( 0==strncmp(ipaddr,"0.0.0.0", 16) ){
		srv_socket_addr.sin_addr.s_addr   = htonl( INADDR_ANY );	/* sin_addr   */
	}else{
		inet_aton( ipaddr, &(srv_socket_addr.sin_addr) );			/* sin_addr   */
	}
	srv_socket_addr.sin_port   = htons( (unsigned short)port );		/* sin_port   */
	sockaddr_size = sizeof(struct sockaddr_in);
	if( connect(socketFD, (struct sockaddr *)&srv_socket_addr, sockaddr_size ) < 0){
		perror("connect");
		exit(EXIT_FAILURE);
	}

	send_and_recv(socketFD);

	close(socketFD);
	return 0;
}

