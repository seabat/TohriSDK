#include <stdio.h>
#include <string.h>

#include "command.h"

static int commandA(char* inBuf, char* outBuf){
	return 0;
}

static int commandB(char* inBuf, char* outBuf){
	return 0;
}

int dispatch_command(char* inBuf, char* outBuf){
	memcpy(outBuf, inBuf, BUFFER_SIZE);
	if( NULL!=strchr(inBuf,'\n') ){
		return 1;
	}else{
		return 0;
	}
}

