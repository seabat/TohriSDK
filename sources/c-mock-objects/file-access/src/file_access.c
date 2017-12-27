
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "log.h"
#include "file_access.h"
#include "file_access_impl.h"

typedef struct func_pointer{
	FP_OPEN_TYPE            open;
	FP_CLOSE_TYPE           close;
	FP_WRITE_TYPE           write;
	FP_READ_TYPE            read;
	FP_GET_SIZE_TYPE        get_size;
	FP_GET_TOTAL_READ_TYPE  get_total_read_size;
	FP_GET_TOTAL_WRITE_TYPE get_total_write_size;
	FP_MKDIR_TYPE           mkdir;
}func_pointer_st;

/* "typedef struct" is in file_access.h. */
struct file_access_info {
	file_st*         data;
	func_pointer_st* fp;
};

/* Assign each function addrees to a function pointer. */
//static func_pointer_st g_fp = {
//	.open	              = openEx,
//	.close	              = closeEx,
//	.write	              = writeEx,
//	.read	              = readEx,
//	.get_size	          = get_size,
//	.get_total_read_size  = get_total_read_size,
//	.get_total_write_size = get_total_write_size,
//	.mkdir	              = mkdirEx,
//};

FileAccess* FileAccess_New( ){
	FileAccess* p_file_info = NULL;

	LOGD( ">> Enter" );
	p_file_info = (FileAccess*)malloc( sizeof(FileAccess) );
	LOGD( "FileAccess address=%p", p_file_info );
	p_file_info->fp = (func_pointer_st*)malloc( sizeof(func_pointer_st) );
	LOGD( "functtion_pointer address=%p", p_file_info->fp );

//	(*p_file_info)->fp = &g_fp;
	p_file_info->fp->open   = openEx;
	p_file_info->fp->close  = closeEx;
	p_file_info->fp->write  = writeEx;
	p_file_info->fp->read   = readEx;
	p_file_info->fp->get_size= get_size;
	p_file_info->fp->get_total_read_size  = get_total_read_size;
	p_file_info->fp->get_total_write_size = get_total_write_size;
	p_file_info->fp->mkdir	= mkdirEx;
	LOGD( "<< Exit" );
	return p_file_info;
}

void FileAccess_Delete( FileAccess** p_file_info ){
	LOGD( "function_pointer address=%p", (*p_file_info)->fp );
	free( (*p_file_info)->fp );
	(*p_file_info)->fp=0;
	LOGD( "function_pointer address=%p", (*p_file_info)->fp );

	LOGD( "FileAccess address=%p", *p_file_info );
	free( *p_file_info );
	*p_file_info=0;
	LOGD( "FileAccess address=%p", *p_file_info );
}

int FileAccess_Open( FileAccess* p_file_access 
					 , const char* mode_str
					 , const char* fname){
	return p_file_access->fp->open( &(p_file_access->data)
							  ,mode_str
							  ,fname );
}

int FileAccess_Close( FileAccess* p_file_access ) {
	return p_file_access->fp->close( p_file_access->data );
}

int FileAccess_Write( FileAccess* p_file_access, const unsigned char* buf, unsigned long long  size ) {
	return p_file_access->fp->write( p_file_access->data, buf, size );
}

int FileAccess_Read( FileAccess* p_file_access, unsigned char* buf, unsigned char* total_buf, unsigned long long size ) {
	return p_file_access->fp->read( p_file_access->data, buf, total_buf, size );
}

int FileAccess_GetSize( FileAccess* p_file_access ) {
	return p_file_access->fp->get_size( p_file_access->data );
}

int FileAccess_GetTotalReadSize( FileAccess* p_file_access ) {
	return p_file_access->fp->get_total_read_size( p_file_access->data );
}

int FileAccess_GetTotalWriteSize( FileAccess* p_file_access ) {
	return p_file_access->fp->get_total_write_size( p_file_access->data );
}

