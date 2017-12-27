#include <string.h>
#include <stdio.h>
#include "sws_util.h"
#include "libsbt/sbt_log.h"

int sws_get_doc_uri( char* str_dst_uri, int str_dst_uri_size, const char* str_src_uri, const char* str_format ){
	int ret = 0;
	int idx = 0;
	char* str_tmp_uri = NULL;
	
	if( NULL==str_dst_uri ){
		LOGW( "The output uri is null" );
		ret = -1;
		goto error;
	}

	if( NULL==str_src_uri ){
		LOGW( "The input uri is null" );
		ret = -1;
		goto error;
	}

	if( 1>strlen(str_src_uri) ){
		LOGW( "The uri length is too short" );
		ret = -1;
		goto error;
	}

	if( NULL==str_format ){
		LOGW( "The format is null" );
		ret = -1;
		goto error;
	}

	if( NULL!=strstr(str_src_uri,"~") ){
		LOGW( "~ is invalid" );
		ret = -1;
		goto error;
	}

	if( NULL!=strstr(str_src_uri,"..") ){
		LOGW( ".. is invalid" );
		ret = -1;
		goto error;
	}

	/* uri         : /index.html  */
	/* =>                         */
	/* str_tmp_uri : index.html   */
	idx = 0;
	while( ('\0'!=str_src_uri[idx]) && ('/'==str_src_uri[idx]) ){
		str_tmp_uri = (char*)(str_src_uri + idx + 1);
		idx++;
	}

	/* When the first byte is null, it is error.                        */
	/* But if the source uri is "/", set "index.html" to the dest uri. */
	if( '\0'==str_tmp_uri[0] ){
		if( ('/'==str_src_uri[0]) && ('\0'==str_src_uri[1]) ){
			strncpy( str_tmp_uri, "index.html", strlen("index.html") );
		}else{
			LOGW( "uri is invalid" );
			ret = -1;
			goto error;
		}
	}

	/* str_tmp_uri    : index.html                        */
	/* str_format : ../data/sbt-web-server/%s         */
	/* =>                                             */
	/* str_dst_uri: ../data/sbt-web-server/index.html */
	snprintf( str_dst_uri, str_dst_uri_size, str_format,  str_tmp_uri );
	LOGD( "uri=%s", str_dst_uri );

error:
	return ret;
}
