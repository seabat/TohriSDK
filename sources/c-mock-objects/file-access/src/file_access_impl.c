#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "file_access.h"
#include "file_access_impl.h"
#include "log.h"

int openEx(file_st** fst, const char* mode_str, const char* fname){
	struct stat stat_buf;
	file_st*    p_local_fst = NULL;
	int			rt          = FILE_CONTROL_OK;

	LOGD( ">> Enter" );

	if(NULL==mode_str || NULL==fname){
		return FILE_CONTROL_PARAM_ERROR;
	}

	*fst = NULL;

	LOGD( "fname=%s mode_str=%s", fname, mode_str );

	p_local_fst = (file_st*)malloc( sizeof(file_st) );
	LOGD( "file_st address=%p", p_local_fst );
    memset( p_local_fst, 0x00,  sizeof(file_st) );
    strncpy(p_local_fst->fname, fname, FILE_NAME_SIZE-1);

	/* file open */
	p_local_fst->fp   = fopen( fname, mode_str );
	if(NULL==p_local_fst->fp){
		LOGE( "%s", strerror(errno) );
		rt = FILE_CONTROL_PARAM_ERROR;
		goto err;
	}

	if( 0!=stat( fname, &stat_buf ) ){
		LOGE( "%s", strerror(errno) );
		rt = FILE_CONTROL_PARAM_ERROR;
		goto err;
	}

	p_local_fst->size = stat_buf.st_size;
	LOGD( "size=%d", p_local_fst->size );

	*fst = p_local_fst;
	LOGD( "<< Exit" );
	return rt;

err:
	if( NULL!=p_local_fst->fp ){
		fclose(p_local_fst->fp);
	}

	if( NULL!=p_local_fst ){
		free( p_local_fst );
	}

	LOGD( "<< Exit rt=%d", rt );
	return rt;
}

int closeEx(file_st* fst){
	LOGD( ">> Enter" );

	if(NULL==fst){
		return FILE_CONTROL_PARAM_ERROR;
	}

	LOGD( "file_st address=%p", fst );
	if( NULL!=fst->fp ){
		fclose(fst->fp);
		fst->fp=NULL;
	}

	if( NULL!=fst ){
		free( fst );
		fst=NULL;
	}

	LOGD( "file_st address=%p", fst );

	LOGD( "<< Exit" );
	return FILE_CONTROL_OK;

}

int writeEx(file_st* fst, const unsigned char* buf, unsigned long long size){
	unsigned long long writed_size = 0;

	LOGD( ">> Enter" );

	if(NULL==fst){
		return FILE_CONTROL_PARAM_ERROR;
	}

	writed_size=fwrite(buf, size, 1, fst->fp);
	if(0>=writed_size){
		return FILE_CONTROL_FATAL_ERROR;
	}

	fst->total_write_size+=size;
	LOGD( "fst->total_write_size=%Ld", fst->total_write_size );

	LOGD( "<< Exit" );
	return FILE_CONTROL_OK;
}

int readEx(file_st* fst, unsigned char* buf, unsigned char* total_buf, unsigned long long size){
	unsigned long long read_size = 0;

	LOGD( ">> Enter" );
	LOGD( "size=%Ld", size );

	if(NULL==fst || NULL==buf || 0==size){
		return FILE_CONTROL_PARAM_ERROR;
	}

	if( fst->size <= fst->total_read_size ){
		LOGW( "no more read" );
		return FILE_CONTROL_NO_MORE_READ_ERROR;
	}

	if( fst->size < fst->total_read_size + size ){
		size = fst->size - fst->total_read_size;
	}

	read_size=fread(buf, size, 1, fst->fp);
	if(0>=read_size){
		return FILE_CONTROL_FATAL_ERROR;
	}

    if(NULL!=total_buf){
		memcpy(total_buf+fst->total_read_size, buf, size);
	}

	fst->total_read_size += size;
	LOGD( "fst->total_read_size=%Ld", fst->total_read_size );

	LOGD( "<< Exit" );
	return FILE_CONTROL_OK;
}

int mkdirEx(const char* base_dir, const char* add_dir){
#if 0
	char prt_dir[512] ={0};
	char chd_dir[512] ={0};
	char tmp_dir[512] ={0};
	char new_dir[512] ={0};
	int  i, j;

	LOGD( ">> Enter" );

	memset( prt_dir, '\0', sizeof(prt_dir) );
	memset( tmp_dir, '\0', sizeof(tmp_dir) );

	getcwd(prt_dir, sizeof(prt_dir));
	if('\0'==prt_dir[0]){
		goto err;
	}

	LOGD("current directory=%s\n", prt_dir);
	LOGD( ">> Exit" );

	return 0;
	for(i=0; i<=strlen(fullpath); i++){
		if(prt_dir[i]==fullpath[i]){
			chd_dir[i]=fullpath[i];
		}else{
			chd_dir[i]='\0';
			break;
		}
	}

	LOGD("current directory=%s\n", prt_dir);

	j=0;
	for(i=0; i<=strlen(dirname); i++){
		if('\0'==dirname[i]){
			break;
		}
		if('/'!=dirname[i]){
			/* Get a charctor */
			tmp_dir[j]=dirname[i];
			j++;
		}else{
			/* Set a directory string */
			tmp_dir[i]='\0';
			LOGD( "tmp_dir=%s", tmp_dir );

			mkdir(tmp_dir, 0755);

			snprintf( new_dir, 512, "%s/%s", prt_dir, tmp_dir );
			memset  ( prt_dir, '\0', sizeof(prt_dir) );
			snprintf( prt_dir, 512, "%s", new_dir );
			LOGD("current directory=%s\n", prt_dir);
			chdir   ( prt_dir );

			memset( tmp_dir, '\0', sizeof(tmp_dir) );
			memset( new_dir, '\0', sizeof(new_dir) );
			j=0;
		}
	}
err:
	LOGE( "%s", strerror(errno) );
#else
	return FILE_CONTROL_NOT_SUPPORT;
#endif
}

int get_size(file_st* fst){
	return fst->size;
}

int get_total_read_size(file_st* fst){
	return fst->total_read_size;
}

int get_total_write_size(file_st* fst){
	return fst->total_write_size;
}

