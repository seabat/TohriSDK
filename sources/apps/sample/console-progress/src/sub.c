#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include <pthread.h>
#include <sys/types.h> /* getpid() */
#include <unistd.h>    /* getpid() */

#include "common.h"

typedef struct _append_file_st{
	char* buf;
	int  size;
}append_file_st;

/**
 * Dispay a progress bar on the console.<br/>
 * Output a progress information to stderr.
 *
 * @param prog_num [IN/OUT] A rate of a progeress bar.
 * @param progress [IN] A current value.
 * @param max      [IN] A max value,
 * @return None
 * @note   prog_num:
 *           This function sets a new rate value to the param of prog_num.
 *           At first, the param of prog_num is set a value of zero.
 *           After the 2nd time, it is set a previous value which is set by this function.
 *         progress:
 *           A current value.
 *         max:
 *           A max value. Do not change this from first to last.
 */
void progress_print(unsigned int* prog_num, unsigned long long progress, unsigned long long max){
/*
 * Max data  :400
 * Max width : 80
 * Rate      : (Max data) / (Max width)
 *             400/80 = 5
 *
 * Progess   : 172
 * Print     : (Progess) / (Rate)
 *             172/5 = 30
 */
	unsigned int   MAX_WIDTH    = 40;
	unsigned long long rate     = 0;
	unsigned int   new_prog_num = 0;
	unsigned char* prog_bar     = NULL;

	if( NULL==prog_num ){
		return;
	}

	rate     = max / (unsigned long long)MAX_WIDTH;
	new_prog_num = (unsigned int)(progress / rate);
	LOGI("progress=%lld rate=%lld new_prog_num=%d\n", progress,rate,new_prog_num);

	prog_bar = (unsigned char*)malloc(MAX_WIDTH+1);
	memset( prog_bar, 0x00, MAX_WIDTH+1 );
	memset( prog_bar, '*', new_prog_num );
	memset( prog_bar+new_prog_num, '-', MAX_WIDTH-new_prog_num );

#if 0
	if( (MAX_WIDTH!=new_prog_num) && (new_prog_num <= *prog_num) ){
		switch( *(prog_bar+new_prog_num) ) {
			case '-':
				memset( prog_bar+new_prog_num, '|', 1);
				break;
			case '|':
				memset( prog_bar+new_prog_num, '-', 1);
				break;
			default:
				break;
		}
	}
#endif

	/* Set a progress bar to a stderr's buffer */
	fprintf( stderr, "%s",prog_bar );

	/* Set a detailed value corresponding to a stderr's buffer */
	fprintf( stderr, "(%lld/%lld)", progress, max );

	/* Set not a new line code but a return code to the rate to a stderr's buffer  */
    fprintf( stderr,"\r");

	/* Output a stderr's buffer */
	fflush( stderr );

	if( MAX_WIDTH==new_prog_num ){
       fprintf( stderr, "\n" );
	}

	*prog_num = new_prog_num;
	if( NULL==prog_bar ){
		free(prog_bar);
	}
	return;
}

void append_file(append_file_st* apd){
	FILE*       fp               = NULL;
	int         write_size        = 0;

	LOGD( "Enter" );
#if 0
	/* file open */
	fp=fopen("test_copy.txt","a");
	if(NULL==fp){
		LOGE( "%s", strerror(errno) );
		goto exit;
	}

	write_size=fwrite(apd->buf, 1, apd->size, fp);

exit:
	if( NULL!=fp ){
		fclose(fp);
	}
#else
	usleep(1000);
	/* dump reading data */
	DUMP( p_file_buf, 0, total_read_size-1 );
#endif
	LOGD( "Exit" );
}

void append_file_thread( char* buf, int size ){
    pthread_t       thread;
	pthread_attr_t  attr;
	append_file_st* apd;

	apd = (append_file_st*)malloc( sizeof(append_file_st) );
	memset( apd, 0x00, sizeof(append_file_st) );
	apd->buf = (char*)malloc(size);
	memcpy(apd->buf, buf, size);
	apd->size = size;

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 64 * 1024);

	pthread_create( &thread, NULL, (void*)append_file, (append_file_st*)apd );

	LOGD("%s(0x%x): Wait   main thread\n",__func__, getpid());
	pthread_join( thread, NULL );
	LOGD("%s(0x%x): Resume main thread\n",__func__, getpid());
	pthread_attr_destroy(&attr);

	if(NULL!=apd->buf){
		free(apd->buf);
	}
	if(NULL!=apd){
		free(apd);
	}
}

void subfunc(){
	FILE*       fp               = NULL;
	struct stat stat_buf;
	char*        p_file_buf       = NULL;
	char         buf[16]          = {0};
	int          read_size        = 0;
	int          total_read_size  = 0;
	unsigned int prog_num         = 0

	LOGD( "Enter" );

	if( 0!=stat( "test.txt", &stat_buf ) ){
		LOGE( "%s", strerror(errno) );
		goto exit;
	}

	LOGD( "file size=%d",stat_buf.st_size );
	if(0>=stat_buf.st_size){
		LOGE( "0 byte" );
		goto exit;
	}

	p_file_buf=(char*)malloc( stat_buf.st_size );

	/* file open */
	fp=fopen("test.txt","r");
	if(NULL==fp){
		LOGE( "%s", strerror(errno) );
		goto exit;
	}

	/* file read */
	while( 0<(read_size=fread(buf, 1, sizeof(buf), fp)) ){
		append_file_thread( buf, sizeof(buf) );
		memcpy( &p_file_buf[total_read_size], buf, read_size );
		total_read_size += read_size;

		/* Display progress bar */
		progress_print( &prog_num, total_read_size, stat_buf.st_size );
	}

exit:
	if( NULL!=fp ){
		fclose(fp);
	}

	if( NULL!=p_file_buf ){
		free( p_file_buf );
	}

	LOGD( "Exit" );

	return;
}
