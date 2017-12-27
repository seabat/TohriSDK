#include <stdio.h>

#include "res.h"
#include "log.h"
#include "file_access.h"

void subfunc(const char* src_path, const char* dst_path){
	unsigned char        buf[50]         = {0};
	unsigned char        total_buf[256]  = {0};
	int                   ret            = 0;
	unsigned long long   src_total_size  = 0;
	FileAccess* pFileAccess;

	LOGD( ">> Enter" );

	if(NULL==src_path){
		LOGE( "param error" );
		return;	
	}

	pFileAccess = FileAccess_New( );
	LOGD( "FileAccess object address=%p", pFileAccess );

	/* Source file write */
	ret = FileAccess_Open( pFileAccess, "wb", src_path );
	LOGD( "ret=%d size=%d total_read_size=%d total_write_size=%d"
		 , ret
		 , FileAccess_GetSize(pFileAccess)
		 , FileAccess_GetTotalReadSize(pFileAccess)
		 , FileAccess_GetTotalWriteSize(pFileAccess) );

	FileAccess_Write( pFileAccess, (char*)sample_data, sizeof(sample_data));

	FileAccess_Close( pFileAccess);

	/* Source file read */
	ret = FileAccess_Open( pFileAccess, "rb", src_path );
	LOGD( "ret=%d size=%d total_read_size=%d total_write_size=%d"
		 , ret
		 , FileAccess_GetSize(pFileAccess)
		 , FileAccess_GetTotalReadSize(pFileAccess)
		 , FileAccess_GetTotalWriteSize(pFileAccess) );

	while(-1 < FileAccess_Read( pFileAccess, buf, total_buf, 50 )){
		LOGD( "total_read_size=%d", FileAccess_GetTotalReadSize(pFileAccess) );
	}

	src_total_size=FileAccess_GetTotalReadSize(pFileAccess);

	DUMP(total_buf,0,FileAccess_GetTotalReadSize(pFileAccess)-1);

	FileAccess_Close( pFileAccess );

	/* Dest file write */
	ret = FileAccess_Open( pFileAccess, "wb", dst_path );
	LOGD( "ret=%d size=%d total_read_size=%d total_write_size=%d"
		 , ret
		 , FileAccess_GetSize(pFileAccess)
		 , FileAccess_GetTotalReadSize(pFileAccess)
		 , FileAccess_GetTotalWriteSize(pFileAccess) );

	FileAccess_Write( pFileAccess, total_buf, src_total_size);

	FileAccess_Close( pFileAccess);

	/* Dest file read */
	ret = FileAccess_Open( pFileAccess, "rb", dst_path );

	while(-1 < FileAccess_Read( pFileAccess, buf, total_buf, 50 )){
		LOGD( "pFileAccess->data->total_read_size=%d", FileAccess_GetTotalReadSize(pFileAccess) );
	}

	DUMP(total_buf,0,FileAccess_GetTotalReadSize(pFileAccess)-1);

	FileAccess_Close( pFileAccess );

	FileAccess_Delete( &pFileAccess );

	LOGD( "<< Exit" );

	return;
}

int main(int argc, char **argv){

	LOGD("Start");

	if(3 != argc){
		LOGE("A number of argument is incorrect.");
		return -1;
	}

	LOGD("Source Path is %s  Dest Path is %s", argv[1], argv[2]);

	// function call
	subfunc(argv[1], argv[2]);

	LOGD("Exit");

	return 0;
}

