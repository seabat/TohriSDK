#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "common.h"

void subfunc(){
	FILE*       fp               = NULL;
	struct stat stat_buf;
	char*       p_file_buf       = NULL;
	char        buf[256]         = {0};
	int         read_size        = 0;
	int         total_read_size   = 0;

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
		memcpy( &p_file_buf[total_read_size], buf, read_size );
		total_read_size += read_size;
	}

	/* dump reading data */
	DUMP( p_file_buf, 0, total_read_size-1 );

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
