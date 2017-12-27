#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sbt_alloc.h"
#include "sbt_log.h"

#ifdef SBT_USE_CUSTUM_ALLOC
#define MALLOC(a) sbt_malloc(a)
#define FREE(a)   sbt_free(a)
#else
#define MALLOC(a) malloc(a)
#define FREE(a)   free(b)
#endif

void sbt_web_html_parse(char** outBuf,const char* inBuf){

//	int  DBG       = 0;
	char textBuf[1024] = {'\0'};
	int  in_len;
	int  i;
	int  tagStatus = 0;
	int  outLen    = 0;

	in_len = strlen( inBuf );

	for(i=0; i<in_len; i++){
		if( 0 == tagStatus ){
			if('>' == inBuf[i]){
				tagStatus = 1;
			}
		}else if(1 == tagStatus){
			if('<' == inBuf[i]){
				tagStatus = 0;
			}else if(' ' == inBuf[i]){
				/* Do nothing */
			}else{
				tagStatus = 2;
				textBuf[outLen] = inBuf[i];
				outLen++;
			}
		}else if(2 == tagStatus){
			if('<' == inBuf[i]){
				tagStatus = 0;
				continue;
			}else{
				textBuf[outLen] = inBuf[i];
				outLen++;
			}
		}
	}

	if(0==outLen){
		*outBuf = NULL;
	}else{
		*outBuf = MALLOC( outLen );
		memset( *outBuf, '\0', outLen );
		strcpy( *outBuf, textBuf );
	}

	return;
}

void sbt_web_html_parse_test(){
	char  *p_buf = NULL;
	char html_test1[]={"<html><body>aaa</body></html>"};
	char html_test2[]={"<html> <body> bbb  </body> </html>"};

	sbt_web_html_parse( (char**)&p_buf,(const char*)html_test1 );
	assert( 0  == strcmp(p_buf,"aaa") );
	if(NULL!=p_buf) sbt_free(p_buf);

	sbt_web_html_parse( (char**)&p_buf,(const char*)html_test2 );
	assert( 0  == strcmp(p_buf,"bbb  ") );
	if(NULL!=p_buf) sbt_free(p_buf);
}
