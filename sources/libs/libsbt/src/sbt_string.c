#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "sbt_string.h"
#include "sbt_log.h"
#include "sbt_alloc.h"

#ifdef SBT_USE_CUSTUM_ALLOC
#define MALLOC(a) sbt_malloc(a)
#define FREE(a)   sbt_free(a)
#else
#define MALLOC(a) malloc(a)
#define FREE(a)   free(b)
#endif
/*--------------------------------------*/
/*  Replace string                      */
/*--------------------------------------*/

int sbt_string_get_strchg_len(const char *buf, const char* before_str, const char* after_str){
	int   DBG = 0;
	int   buf_len;
	const char* p_temp_buf;
	int   chg_after_len=0;
	int   dif_len      =0;

	if( (NULL==buf)||(NULL==before_str)||(NULL==after_str) ){
		LOGD("invalid parameter");
		return -1;
	}

	if( ('\0'==*buf)||('\0'==*before_str)||('\0'==*after_str) ){
		LOGD("invalid parameter");
		return -1;
	}

	buf_len = strlen(buf);
	dif_len = strlen(after_str) - strlen(before_str);
	if(DBG) LOGD("buf_len=%d dif_len=%d", buf_len, dif_len);

	p_temp_buf = buf;
	while ((p_temp_buf = strstr(p_temp_buf, before_str)) != NULL) {
		/* p_temp_bufを先頭とする文字列から文字列befor_strを探す。*/
		/* 見つかったらそのアドレスをp_temp_bufに設定する。       */
		/* 見つからなくなるまで繰り返す。                         */
		
		chg_after_len = chg_after_len + dif_len;
		if(DBG) LOGD("chg_afer_len=%d", chg_after_len);
		if(DBG) LOGD("adress=%d value=%c", p_temp_buf, *p_temp_buf);
		p_temp_buf = p_temp_buf + strlen(before_str);
	}
	return ( buf_len + chg_after_len );
}

int sbt_string_strchg(char** chg_buf, char *src_buf, const char *before_str, const char *after_str)
{
	int  DBG = 0;
	char p_buf[1024 + 1] = {'\0'};
	char *p          = NULL;
	char *p_res      = NULL;
	int  chg_buf_len = 0;

	if( (NULL==src_buf)||(NULL==before_str)||(NULL==after_str) ){
		LOGD("invalid parameter");
		return -1;
	}

	if( ('\0'==*src_buf)||('\0'==*before_str)||('\0'==*after_str) ){
		LOGD("invalid parameter");
		return -1;
	}

	chg_buf_len = sbt_string_get_strchg_len(src_buf, before_str, after_str);
	*chg_buf = MALLOC( chg_buf_len );
	memset( *chg_buf, '\0', chg_buf_len);
	memcpy(p_buf, src_buf, strlen(src_buf)+1);

	p = p_buf;
	while ((p_res = strstr(p, before_str)) != NULL) {  /* step1  */
		/* 見つからなくなるまで繰り返す  */
		if(DBG) LOGD("adress=%d value=%c", p_res, *p_res);
		*p_res = '\0';                                /* step2 */
		if(DBG) LOGD("value=%s", p);
		strcat( (*chg_buf), p );                      /* step3 */
		strcat( (*chg_buf), after_str );              /* step4 */
		p_res = p_res + strlen(before_str);           /* step5 */
		p = p_res;							          /* step6 */
		p_res = NULL;
		if(DBG) LOGD("last string=%s",p);
	}

	if(DBG) LOGD("last string=%s",p);
	strcat( (*chg_buf), p );                          /* step7 */

	return 0;
}

/*
 src_buf= {'a','b','c','d','b','c','e','\0'} 
 before_str={'b','c','\0'}
 after_str ={'x','y','\0'}

[step1]
        +---------------------+
0x0000  | 'a'
0x0001  | 'b'                   ← 見つけた場所のアドレスがp_resに格納される
0x0002  | 'c'
0x0003  | 'd'
0x0004  | 'b'
0x0005  | 'c'
0x0006  | 'e'
0x0007  | '\0'
        +---------------------+
p		+---------------------+
0x1000  | 0x0000
        +---------------------+
p_res	+---------------------+
0x2000  | 0x0001
        +---------------------+

[step2]
        +---------------------+
0x0000  | 'a'
0x0001  | '\0'					← p_resが指すポインタのにNULL文字 ('\0')を設定する
0x0002  | 'c'					  後でstrcat()をするための準備
0x0003  | 'd'
0x0004  | 'b'
0x0005  | 'c'
0x0006  | 'e'
0x0007  | '\0'
        +---------------------+
p		+---------------------+
0x1000  | 0x0000
        +---------------------+
p_res	+---------------------+
0x2000  | 0x0001
        +---------------------+

[step5]
        +---------------------+
0x0000  | 'a'
0x0001  | '\0'
0x0002  | 'c'
0x0003  | 'd'					← p_resを検索対象の先頭に移動
0x0004  | 'b'
0x0005  | 'c'
0x0006  | 'e'
0x0007  | '\0'
        +---------------------+
p		+---------------------+
0x1000  | 0x0000
        +---------------------+
p_res	+---------------------+
0x2000  | 0x0003
        +---------------------+

[step6]
        +---------------------+
0x0000  | 'a'
0x0001  | '\0'
0x0002  | 'c'
0x0003  | 'd'
0x0004  | 'b'
0x0005  | 'c'
0x0006  | 'e'
0x0007  | '\0'
        +---------------------+
p		+---------------------+
0x1000  | 0x0003				← p_resをpにコピー
        +---------------------+
p_res	+---------------------+
0x2001  | 0x0003
        +---------------------+

[step7]
        +---------------------+
0x0000  | 'a'
0x0001  | '\0'
0x0002  | 'c'
0x0003  | 'd'
0x0004  | '\0'
0x0005  | 'c'
0x0006  | 'e'					← p={'e','\0'}を置換後文字列にstrcat()する
0x0007  | '\0'
        +---------------------+
p		+---------------------+
0x1000  | 0x0006
        +---------------------+
p_res	+---------------------+
0x2001  | 0x0000				← 被置換文字列が見つからないのでNULL
        +---------------------+
*/

#define SBT_STRING_MAX_SPLIT_NUM 100
char* gp_split_str_list[SBT_STRING_MAX_SPLIT_NUM];

int sbt_string_split( char** split_str_list, 
					  int    list_num,
					  char*  src_buf, 
					  unsigned long long src_size, 
					  const char* token_str ){
	unsigned long long idx = 0;
	unsigned int       jdx = 0;
	char*              split_str = NULL;
	int                split_num = 0;

	if(NULL==src_buf){
		return 0;
	}

	if(NULL==token_str){
		return 0;
	}

	split_str = &src_buf[0];

	for(idx=0; idx<src_size; idx++){
		for(jdx=0; jdx<strlen(token_str)+1; jdx++){
			if( (token_str[jdx] == src_buf[idx]) && 
				(list_num > split_num) ){
				src_buf[idx] = '\0';
				if( 0 < strlen(split_str) ){
					split_str_list[split_num] = split_str;
					split_num++;
				}else{
					/* If a first byte of src_buf[] is a token, the split_str is ignored */
					/* If a token is appeared for two bytes, the split_str is ignored        */
				}
				/* Set next split buf */
				split_str = &src_buf[idx+1];
				break;
			}
		}
	}
	return split_num;
}


void sbt_string_test(){
	int  chg_buf_len = 0;
	char  *chg_buf = NULL;

	/* For sbt_string_split */
	char*  split_str_list[10]; 
	char   data1_for_split[] = "aaa bbb ccc";
	char   data2_for_split[] = "ddd eee\nfff";
	char   data3_for_split[] = "";
	char   data5_for_split[] = "aaa bbb ccc";
	char   data6_for_split[] = "aaa bbb ccc";
	char   data7_for_split[] = "ggggggggggggg e fffff gggg ";
	char   data8_for_split[] = " ggggggggggggg  e fffff gggg ";
	char   data9_for_split[] = {'a','a','a',' ','b','b',};
	int    split_num      = 0;

	/* 置換後の文字列長が置換前の文字列長より長くなる場合 */
	LOGD("test1-1 sbt_string_get_strchg_len(\"abcdefbcgh\",\"bc\",\"xyz\");");
	chg_buf_len = sbt_string_get_strchg_len("abcdefbcgh","bc","xyz");
	assert( 12 == chg_buf_len );

	/* 置換後の文字列長が置換前の文字列長より短くなる場合 */
	LOGD("test1-2 change buffer len");
	chg_buf_len = sbt_string_get_strchg_len("abcdefbcgh","bc","b");
	assert( 8 == chg_buf_len );

	/* 被置換文字列と置換文字列が同じ場合 */
	LOGD("test1-3 change buffer len");
	chg_buf_len = sbt_string_get_strchg_len("abcdefbcgh","bc","bc");
	assert( 10 == chg_buf_len );
	
	/* 全体の文字列が空の場合 */
	LOGD("test1-4 change buffer len");
	chg_buf_len = sbt_string_get_strchg_len("","bc","xyz");
	assert( -1 == chg_buf_len );

	/* 被置換文字列が空の場合 */
	LOGD("test1-5 change buffer len");
	chg_buf_len = sbt_string_get_strchg_len("abcdefbcgh","","xyz");
	assert( -1 == chg_buf_len );

	/* 置換文字列が空の場合 */
	LOGD("test1-6 change buffer len");
	chg_buf_len = sbt_string_get_strchg_len("abcdefbcgh","bc","");
	assert( -1 == chg_buf_len );

	/* 置換後の文字列長が置換前の文字列長より長くなる場合 */
	LOGD("test2-1 change buffer");
	sbt_string_strchg( (char**)&chg_buf, "abcdefbcgh", "bc", "xyz");
	assert( 0  == strcmp(chg_buf,"axyzdefxyzgh") );
	
	FREE(chg_buf);
	
	/* 置換後の文字列長が置換前の文字列長より短くなる場合 */
	LOGD("test2-2 change buffer");
	sbt_string_strchg( (char**)&chg_buf, "abcdefbcgh", "bc", "z");
	assert( 0  == strcmp(chg_buf,"azdefzgh") );
	
	FREE(chg_buf);

	/* test sbt_string_split_*/
	LOGD("test3-1 split string");
	split_num = sbt_string_split( split_str_list, 10, data1_for_split, sizeof(data1_for_split), " " );
	assert( 3==split_num );
	assert( 0 == strcmp("aaa",split_str_list[0]));
	assert( 0 == strcmp("bbb",split_str_list[1]));
	assert( 0 == strcmp("ccc",split_str_list[2]));

	LOGD("test3-2 split string");
	split_num = sbt_string_split( split_str_list, 10, data2_for_split, sizeof(data2_for_split), " \n" );
	assert( 3==split_num );
	assert( 0 == strcmp("ddd",split_str_list[0]));
	assert( 0 == strcmp("eee",split_str_list[1]));
	assert( 0 == strcmp("fff",split_str_list[2]));

	LOGD("test3-3 split string");
	split_num = sbt_string_split( split_str_list, 10, data3_for_split, sizeof(data3_for_split), " " );
	assert( 0==split_num );

	LOGD("test3-4 split string");
	split_num = sbt_string_split( split_str_list, 10, NULL, sizeof(data1_for_split), " " );
	assert( 0==split_num );

	LOGD("test3-5 split string");
	split_num = sbt_string_split( split_str_list, 10, data5_for_split, sizeof(data5_for_split), NULL );
	assert( 0==split_num );

	LOGD("test3-6 split string");
	split_num = sbt_string_split( split_str_list, 10, data6_for_split, sizeof(data6_for_split), "" );
	assert( 1==split_num );
	assert( 0 == strcmp("aaa bbb ccc",split_str_list[0]));

	LOGD("test3-7 split string");
	split_num = sbt_string_split( split_str_list, 10, data7_for_split, sizeof(data7_for_split), " " );
	assert( 4==split_num );
	assert( 0 == strcmp("ggggggggggggg",split_str_list[0]));
	assert( 0 == strcmp("e",split_str_list[1]));
	assert( 0 == strcmp("fffff",split_str_list[2]));
	assert( 0 == strcmp("gggg",split_str_list[3]));


	LOGD("test3-8 split string");
	split_num = sbt_string_split( split_str_list, 10, data8_for_split, sizeof(data8_for_split), " " );
	assert( 4==split_num );
	assert( 0 == strcmp("ggggggggggggg",split_str_list[0]));
	assert( 0 == strcmp("e",split_str_list[1]));
	assert( 0 == strcmp("fffff",split_str_list[2]));
	assert( 0 == strcmp("gggg",split_str_list[3]));

	LOGD("test3-9 split string");
	split_num = sbt_string_split( split_str_list, 10, data9_for_split, sizeof(data9_for_split), " " );
	assert( 1==split_num );
	assert( 0 == strcmp("aaa",split_str_list[0]));
}

