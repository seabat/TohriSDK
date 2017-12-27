#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>  /* malloc free */
#include <time.h>    /* struct tm, time() */

#include "sbt_log.h"

static unsigned char g_logfile_path[256]={'\0'};

void sbt_logln_tofd(FILE* fd, const char* file_name, const char* level, const char* func_name, int line_no, int pid, const char* format, ...){
	va_list va_args;
	time_t timer;
	struct tm *t_st;

	time(&timer);
	t_st = localtime(&timer);
	fprintf( fd, "%02d-%02d %02d:%02d:%02d %s %s/%s(%d)[%d]: ",
			 t_st->tm_mon+1,
			 t_st->tm_mday,
			 t_st->tm_hour,
			 t_st->tm_min,
			 t_st->tm_sec,
			 level,
             file_name,
			 func_name,
			 line_no,
			 pid );

	va_start(va_args, format);
	vfprintf(fd, format, va_args);
	va_end(va_args);
	fprintf( fd, "\n");
}


void sbt_flogln(const char* level, const char* file_name, const char* func_name, int line_no, int pid, const char* format, ...){
	va_list va_args;
	FILE*   fp;
	time_t  timer;
	struct tm *t_st;

	if('\0'==g_logfile_path[0]){
		fp = fopen( SBT_LOG_FILE, "a");
	}else{
		fp = fopen( (const char*)g_logfile_path, "a");
	}

	if( NULL==fp ){
		perror("can't open file\n");
		return;
	}

	time(&timer);
	t_st = localtime(&timer);
	fprintf( fp, "%02d-%02d %02d:%02d:%02d %s/%s(%d)[%d]: ",
			 t_st->tm_mon+1,
			 t_st->tm_mday,
			 t_st->tm_hour,
			 t_st->tm_min,
			 t_st->tm_sec,
			 level,
			 func_name,
			 line_no,
			 pid );

	va_start( va_args, format );
	vfprintf( fp, format, va_args );
	va_end( va_args );
	fprintf( fp, "\n" );
	fclose(fp);
}

void sbt_flog_init(const char* path){
	if(NULL!=path){
		strcpy((char*)g_logfile_path, path);
	}
}

void sbt_dumpln( const unsigned char* buf, int start_index, int end_index ){

	int i          = 0;
    int dump_size  = 0;
	unsigned char* dump_buf = NULL;

	/* bun[0] <- start_index
	 * bun[1]
	 * bun[2]
	 * bun[3]
	 * bun[4] <- end_index
	 */

	dump_size = end_index - start_index + 1;
	if( 0!=dump_size%16 ){
		dump_size+= 16 - dump_size%16;
	}
	dump_buf  = (unsigned char*)malloc( dump_size );
	memset( dump_buf, 0x00, dump_size );
	memcpy( dump_buf, buf+start_index, end_index - start_index + 1 );

	fprintf(stderr,     "        |+0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");

	for(i=0; i+16<=dump_size; i+=16){ 
		fprintf(stderr, "%08x|%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
				i,
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

void sbt_dump( const unsigned char* buf, int start_index, int end_index ){

	int cur_index = start_index;
	int dump_num   = 0;
	int i          = 0;
//	fprintf(stderr, "end_index=%d\n", end_index);

	fprintf(stderr, "        |+0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");

	do{
		/* Set a number of bytes in one line */
		if( (end_index+1)<=cur_index+16 ){
			dump_num = end_index-cur_index+1;
		}else{
			dump_num = 16;
		}

		fprintf(stderr,"%08x|", cur_index);

		for(i=0; i<dump_num; i++){
			if(i==dump_num-1){
				/* Print last byte */
				fprintf(stderr, "%02x", buf[cur_index+i]);
			}else{
				/* Print no last byte */
				fprintf(stderr, "%02x ", buf[cur_index+i]);
			}
		}

		fprintf(stderr, "\n");
		/* Set first index of a next line */
		cur_index += 16;
	}while( cur_index<=end_index );
}

void sbt_test_log(){
	int  int_arg    = 3;
	unsigned char char_arg[5]={"test"};
	unsigned char dump_arg[38]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
						  ,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f
						  ,0x20,0x21,0x22,0x23,0x24,0x25};

	/* test1 */
	LOGD("DEBUG %d", int_arg); 
	
	/* test2 */
	LOGI("INFO %d", int_arg); 
	
	/* test3 */
	LOGW("WARNING %d", int_arg); 
	
	/* test4 */
	LOGE("ERROR %d", int_arg); 
	
	/* test5 */
	FLOGD("DEBUG %d",int_arg);

	/* test6 */
	FLOGI("INFO %d",int_arg);

	/* test7 */
	FLOGW("WARNING %d",int_arg);

	/* test8 */
	FLOGE("ERROR %d",int_arg);

	/* test9 */
	FLOG_INIT(NULL);
	FLOGI("%d",char_arg);
	
	/* test10 */
	FLOG_INIT("./log2.txt");
	FLOGW("%d",char_arg);

	DUMP( (const unsigned char*)dump_arg, 0, 38-1 );
	DUMP( (const unsigned char*)dump_arg, 16, 38-1 );
	DUMP_LN( (const unsigned char*)dump_arg, 0, 38-1 );
	DUMP_LN( (const unsigned char*)dump_arg, 16, 38-1 );
}

void sbt_mem_dump( void* buf, unsigned long long num){
	int i                = 0;
	unsigned char* c_buf = buf;

	if(4==sizeof(buf)){
		/* 32bit OS */
		fprintf(stderr, "ADDRESS   |VALUE\n");
	}else if(8==sizeof(buf)){
		/* 64bit OS */
		fprintf(stderr, "ADDRESS           |VALUE\n");
	}else{
	}

	for(i=0; i<num; i++){ 
			fprintf(stderr, "%p|%02x\n",
					(unsigned char*)&c_buf[i],
					(unsigned char)c_buf[i]);
	}
	
}

void sbt_test_mem_dump(){
	unsigned char test_ar[]={ 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18
						     ,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28 };
	long long  test_int   = 0x11223344;
	long long* p_test_int = &test_int;

	/* Stack status 
	 0x00000000
		|                 |
	 	+-----------------+
	 	|3rd variable     |
	 	+-----------------+
	 	|2nd variable     |
	 	+-----------------+
	 	|1st variable     |
	 	+-----------------+
	 	|ebp register     |
	 	+-----------------+
	 	|return address   |
	 	+-----------------+
	 	|                 |
	 	+-----------------+
		|                 |
	0xEEEEEEEE
	 */

	fprintf(stderr, "Dump array memory =>\n");
	fprintf(stderr, "Start address is %p\n",&test_ar[0]);
	sbt_mem_dump( (void*)test_ar ,sizeof(test_ar));

	fprintf(stderr, "Dump int memory =>\n");
	fprintf(stderr, "Start address is %p\n",&test_int);
	sbt_mem_dump( (void*)&test_int ,sizeof(long long));

	fprintf(stderr, "Dump int pointer memory =>\n");
	fprintf(stderr, "Start address is %p\n",&p_test_int);
	sbt_mem_dump( (void*)&p_test_int ,sizeof(long long*));

	fprintf(stderr, "Dump all local memory =>\n");
	sbt_mem_dump( (void*)&p_test_int, sizeof(long long*) + sizeof(long long) + sizeof(test_ar));

	fprintf(stderr, "Dump stack memory(with \"ebp\" and \"return address\") =>\n");
	sbt_mem_dump( (void*)&p_test_int, sizeof(long long*) + sizeof(long long) + sizeof(test_ar) + sizeof(void*)  + sizeof(void*) );
}
