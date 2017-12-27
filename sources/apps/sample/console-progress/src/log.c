
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include "common.h"

void log_debug(const char* level, const char* file_name, const char* func_name, int line_no, int pid, const char* format, ...){
	va_list va_args;
	time_t timer;
	struct tm *t_st;

	time(&timer);
	t_st = localtime(&timer);
	fprintf( stderr, "%02d-%02d %02d:%02d:%02d %s/%s(%d)[%d]: ",
			 t_st->tm_mon+1,
			 t_st->tm_mday,
			 t_st->tm_hour,
			 t_st->tm_min,
			 t_st->tm_sec,
			 level,
			 func_name,
			 line_no,
			 pid );

	va_start(va_args, format);
	vfprintf(stderr, format, va_args);
	va_end(va_args);
	fprintf( stderr, "\n");
}

void log_dump( char* buf, int start_index, int end_index ){

	int dump_index = start_index;
	int dump_num   = 0;
	int i          = 0;

	fprintf(stderr, "end_index=%d\n", end_index);

	do{
		if( (end_index+1)<=dump_index+16 ){
			dump_num = end_index-dump_index+1;
		}else{
			dump_num = 16;
		}

		for(i=0; i<dump_num; i++){
			fprintf(stderr, "%02x", buf[dump_index+i]);
		}

		fprintf(stderr, "\n");
		dump_index += 16;
	}while( dump_index<=end_index );
}
