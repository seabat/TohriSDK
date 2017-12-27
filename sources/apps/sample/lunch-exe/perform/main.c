#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "hello_world.h"

void printf_ex( const char* file, const char* func, const char* format, ...);

#if DEBUG
#define PRINT(...) printf_ex( __FILE__, __func__, __VA_ARGS__);
#else
#define PRINT(...)
#endif


int main(int argc, char **argv)
{
	int ret = 0;
	char cmd_buf[50] = {0x00};
	
	PRINT("start\n");

	/* The stdin is keyborad */
	if(3>=argc){
		PRINT("invalid parameter\n");
		goto exit;
	}

	sprintf( cmd_buf, "./hello_command %s %s %s", argv[1], argv[2], argv[3] );
	PRINT("cmd_buf=%s\n",cmd_buf);
	/*ex. ./hello_matsu exec < /home/9004026055/hello_world/hello.xml */

	system( cmd_buf );
	
exit:
	PRINT("end\n");
	return ret;
}

void printf_ex( const char* file, const char* func, const char* format, ...){
	va_list arg;

	printf("[%s][%s]:", file, func);
	va_start(arg, format);
	vprintf( format, arg );
	va_end(arg);
}
