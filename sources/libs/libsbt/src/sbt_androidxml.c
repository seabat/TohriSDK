#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "sbt_log.h"

static int search_res_name(const char* file_name, const char* res_name){
    int   i,j,k   = 0;
    int   cnt     = 0;
    FILE* fp  = NULL;
    char* buf = NULL;;
    int   len_res_name = 0;
    unsigned long long read_size = 0;
	struct stat stat_buf;

    /*
     *  data[]
     *  [00]
     *  [01]
     *  [02]
     *  [03]
     *  [04] <
     *  [05] s
     *  [06] t
     *  [07] r
     *  [08] i
     *  [09] n
     *  [10] g 
     *  [11] -
     *  [12] a
     *  [13] r
     *  [15] r
     *  [16] a 
     *  [17] y
     *
     * UNIXでは、改行コード列は「0x0A」
     * Windowsでは「0x0D 0x0A」
     * Macintoshでは「0x0D」
     *
     */


    len_res_name = strlen(res_name);

	if( 0!=stat( file_name, &stat_buf ) ){
        LOGE( "%s", strerror(errno) );
		goto err;
	}

    LOGD( "file size=%d",stat_buf.st_size );
    buf = (char*)malloc(stat_buf.st_size);

	if(0>=stat_buf.st_size){
		LOGE( "0 byte" );
		goto err;;
	}

    fp = fopen( file_name, "r" ); 
	if(NULL==fp){
		LOGE( "%s", strerror(errno) );
		goto err;
	}

	read_size=fread(buf, 1, stat_buf.st_size, fp);
    if(read_size!=stat_buf.st_size){
		LOGE( "read error" );
		goto err;
    }

    /* Search res_name */
    for( i=0; i<stat_buf.st_size; i++){
        if( '<'==buf[i] ){
            break;
        }
    }

    if(i==stat_buf.st_size){
		LOGE( "xml format error" );
		goto err;
    }
      
    for( j=i; j<stat_buf.st_size; j++){
		LOGD( "Start searching" );
        cnt=0;

        /* Compare a charctor */
        for(k=0; k<len_res_name; k++){
		    LOGD( "%c %c", buf[j+k], res_name[k] );
            if( buf[j+k]==res_name[k] ){
                cnt++;
                if(cnt==len_res_name){
		            LOGD( "stop compare a charactor" );
                    break;
                }
            }else{
                cnt=0;
                break;
            }
        }
        if(cnt==len_res_name){
		     LOGD( "GET!" );
             break;
        }
    }

    if(j==stat_buf.st_size){
		LOGE( "xml format error" );
		goto err;
    }

	LOGD( "offset=0x%02x", j );
    if(NULL!=buf){
        free(buf);
    }
    if(NULL!=fp){
        fclose(fp);
    }
    return j;
err:
    if(NULL!=buf){
        free(buf);
    }
    if(NULL!=fp){
        fclose(fp);
    }
    return -1;

}

int sbt_androidxml_get_array_length(const char* file_name, const char* res_name){

    search_res_name(file_name, res_name);
    return 0;
}

char* sbt_androidxml_get_string_array(const char* file_name, const char* res_name){
    return NULL;
}

int* sbt_androidxml_get_int_array(const char* file_name, const char* res_name){
    return NULL;

}

void test_sbt_androidxml(){

    FILE* fp;
    char xml_test_data1[]={"<integer-array name=\"id\">"};
//    char xml_test_data2[]={"<integer-array name=\"id\">"};

	LOGD( "Start test_sbt_androidxml" );

	LOGD( "test1" );
    fp = fopen( "test.xml", "w" ); 
	if(NULL==fp){
		LOGE( "%s", strerror(errno) );
		goto err;
	}

    fwrite(xml_test_data1, 1, sizeof(xml_test_data1), fp);

    if(NULL!=fp){
        fclose(fp);
    }

    sbt_androidxml_get_array_length( "test.xml", "id");

	LOGD( "test2" );
    sbt_androidxml_get_array_length( "test.xml", "xd");

err:
	LOGD( "End test_sbt_androidxml" );
    fp = fopen( "test.xml", "w" ); 
    return;
}
