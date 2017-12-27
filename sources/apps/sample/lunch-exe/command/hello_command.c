#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void printf_ex( const char* file, const char* func, const char* format, ...);

#if DEBUG
#define PRINT(...) printf_ex( __FILE__, __func__, __VA_ARGS__);
#else
#define PRINT(...)
#endif

#define ASCII_LF (0x0a) 
#define MAX_LINE (10)

int main(int argc, char **argv)
{
	int  ret = 0;
#ifdef STDIN_IS_FILE
	int  i   = 0;
	char line[MAX_LINE][1024] = {0x00};
#endif
	
	PRINT("start\n");
#ifdef STDIN_IS_FILE
	while( MAX_LINE>i && fgets(line[i], sizeof(line[i]),stdin) ){
		PRINT("%s\n", line[i]);
		if( line[i][0]==ASCII_LF ){
			PRINT("%s break fgets\n",__func__);
			break;
		}
		PRINT("%s %c %c %c\n", __func__, line[i][0],line[i][1],line[i][2]);
		i++;
	}
#else
	if(3>=argc){
		PRINT("invalid parameter\n");
		goto exit;
	}
	PRINT( "%s %s %s\n", argv[1], argv[2], argv[3] );
#endif
	PRINT("result=%d\n",3);
	
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
