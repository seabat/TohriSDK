#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "command.h"

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

static int commandA(char* inBuf, char* outBuf){
	return 0;
}

static int commandB(char* inBuf, char* outBuf){
	return 0;
}

int dispatch_command( thread_arg_st* arg ){
	int send_len    = 0;
	int recv_len    = 0;
	char inBuf[500] = {0};
	int in_size = (arg->cmd_in_size[3]) | (arg->cmd_in_size[2]<<8) | (arg->cmd_in_size[1]<<16) | (arg->cmd_in_size[0]<<24);
	arg->p_cmd_in_payload = (unsigned char*)malloc( in_size );

	if( 0>(recv_len=recv(arg->acceptFD, arg->p_cmd_in_payload, in_size, 0)) ){
		perror("recv");
		goto error;	
	}

	sbt_dump(arg->p_cmd_in_payload, 0, in_size-1);
	memcpy(inBuf, arg->p_cmd_in_payload, in_size); 

	/* send */
	send_len = send( arg->acceptFD, inBuf, recv_len, 0 );
error:
	if(NULL!=arg->p_cmd_in_payload) free(arg->p_cmd_in_payload);
	return 0;

}

