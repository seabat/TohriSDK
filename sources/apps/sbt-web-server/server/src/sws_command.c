#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <sys/stat.h>

#include "sws_command.h"
#include "sws_util.h"
#include "libsbt/sbt_log.h"

#define HTTP_STATUS_400_BAD_REQUEST             400
#define HTTP_STATUS_404_NOT_FOUND               404 
#define HTTP_STATUS_500_INTERNAL_SERVER_ERROR   500
#define HTTP_STATUS_501_NOT_IMPLEMENT           501

#define ERROR_STATUS_400_BAD_REQUEST           -400
#define ERROR_STATUS_404_NOT_FOUND             -404 
#define ERROR_STATUS_500_INTERNAL_SERVER_ERROR -500
#define ERROR_STATUS_501_NOT_IMPLEMENT         -501

#define DOC_URI_BUF_SIZE                       1024

static int send_response( int fd, char* data, int size, int flg){
	int send_len = 0;
	int ret      = 0;
	/* send */
	send_len = send( fd, data, size, flg );
	if( 0>send_len ){
		LOGW( "send ret=%d", send_len );
		ret = ERROR_STATUS_500_INTERNAL_SERVER_ERROR;
	}
	return ret;
}

static int send_GET_response(int fd, char* data, int str_len){
	int  ret         = 0;
	char res_format[]= "HTTP/1.0 200 OK\r\n"
                       "Content-Length: %d\r\n"
                       "Content-Type: text/html\r\n"
                       "\r\n"
                       "%s"
                       "\r\n";
	char* res_buf    = NULL;
	int  res_size    = 0;

	res_size = sizeof(res_format) + str_len;
	res_buf = malloc( res_size );
	if(NULL==res_buf){
		LOGW( "Can't alloc" );
		ret = ERROR_STATUS_500_INTERNAL_SERVER_ERROR;
		goto error;
	}

	memset( res_buf, 0x00, res_size );

	snprintf( res_buf, res_size, res_format, str_len, data );
	ret = send_response( fd, res_buf, res_size, 0 );

error:
	if( NULL!=res_buf){
		free(res_buf);
	}
	return ret;
}

static int send_error_response(int fd, int errID){
	int  ret            = 0;
	char res_data[1024] = {0};

	switch(errID){
		case ERROR_STATUS_404_NOT_FOUND:
			snprintf( res_data, sizeof(res_data), "404 Not Found" );
			break;
		case ERROR_STATUS_400_BAD_REQUEST:
			snprintf( res_data, sizeof(res_data), "400 Bad Request" );
			break;
		case ERROR_STATUS_500_INTERNAL_SERVER_ERROR:
			snprintf( res_data, sizeof(res_data), "500 Internal Server Error" );
			break;
		case ERROR_STATUS_501_NOT_IMPLEMENT:
			snprintf( res_data, sizeof(res_data), "501 Not Implemented" );
			break;
		default:
			snprintf( res_data, sizeof(res_data), "400 Bad Request" );
			break;
	}
	
	/* send */
	ret =send_response( fd, res_data, strlen(res_data)+1, 0 );
	return ret;
}

static int process_GET_req(int fd, char* str_uri){
	int   ret             = 0;
	FILE* fp              = NULL;
	struct stat stat_buf;
	char  str_doc_uri[DOC_URI_BUF_SIZE]  = { 0 };
	char* res_buf         = NULL;
	int   read_size       = 0;
	int   total_read_size = 0;
	pthread_t tid       = pthread_self();

	LOGD( "[TID=%p][FD=%d]START", tid, fd );

	if( NULL==str_uri ){
		LOGW( "[TID=%p][FD=%d]uri is null", tid, fd );
		ret = ERROR_STATUS_500_INTERNAL_SERVER_ERROR;
		goto error;
	}

	if( 0>sws_get_doc_uri( str_doc_uri, DOC_URI_BUF_SIZE, (const char*)str_uri, "../data/sbt-web-server/%s" ) ){
		LOGW( "[TID=%p][FD=%d]uri is invalid", tid, fd );
		ret = ERROR_STATUS_400_BAD_REQUEST;
		goto error;
	}

	fp = fopen( str_doc_uri, "rb");
	if(NULL==fp){
		LOGW( "[TID=%p][FD=%d]%s", tid, fd , strerror(errno));
		ret = ERROR_STATUS_404_NOT_FOUND;
		goto error;
	}

	if( 0!=stat( str_doc_uri, &stat_buf ) ){
		LOGW( "[TID=%p][FD=%d]%s", tid, fd , strerror(errno));
		ret = ERROR_STATUS_500_INTERNAL_SERVER_ERROR;
		goto error;
	}

	if(0>=stat_buf.st_size){
		LOGW( "[TID=%p][FD=%d]0 byte", tid, fd );
		ret = ERROR_STATUS_500_INTERNAL_SERVER_ERROR;
		goto error;
	}

	res_buf = malloc( stat_buf.st_size );
	if(NULL==res_buf){
		LOGW( "[TID=%p][FD=%d]Can't alloc", tid, fd );
		ret = ERROR_STATUS_500_INTERNAL_SERVER_ERROR;
		goto error;
	}

	memset( res_buf, 0x00, stat_buf.st_size );

	while( 0<(read_size=fread( &res_buf[total_read_size], 1, sizeof(stat_buf.st_size), fp)) ){
		total_read_size += read_size;
	}

	ret = send_GET_response(fd, res_buf, total_read_size);
//	send_footer_response(fd);

error:
	if(NULL!=fp){
		fclose(fp);
	}

	if( 0>ret ){
		send_error_response( fd, ret );
	}

	if(NULL!=res_buf){
		free(res_buf);
	}

	LOGD( "[TID=%p][FD=%d]END ret=%d", tid, fd, ret );
	return ret;
}

int sws_dispatch_command( thread_arg_st* arg ){
	int ret         = 0;
	char* str_method  =NULL;
	char* str_uri     =NULL;
	char* str_httpver =NULL;
	const char str_token[] =" \n"; /* ' ' or '\n'  is tokens for split */

	/*
	 * "GET /index.html HTTP/1.0"
	 * =>
	 *    str_method  = "GET";
	 *    str_uri     = "/index.html";
	 *    str_httpver = "HTTP/1.0";
	 */

	/*[CAUTION]                                                                     */
	/* A function of strstok() changes a first argument. So don't use the function. */

	LOGD("http_request=%s", arg->http_req_data);
	str_method  = strtok( (char*)arg->http_req_data, str_token );
	str_uri     = strtok( NULL, str_token );
	str_httpver = strtok( NULL, str_token );
	LOGD("method=%s uri=%s httpver=%s", str_method, str_uri, str_httpver);

	if( NULL==str_method || NULL==str_uri || NULL==str_httpver ){
		LOGD("400 Bad Request");
		send_error_response(arg->acceptFD, ERROR_STATUS_400_BAD_REQUEST);
		goto error;
	}

	if( strncmp(str_method, "GET", sizeof("GET"))==0 ){
		process_GET_req( arg->acceptFD, str_uri );
	}else{
		LOGD("501 Not Implemented");
		send_error_response(arg->acceptFD, ERROR_STATUS_501_NOT_IMPLEMENT);
		goto error;
	}

error:
	return ret;
}

