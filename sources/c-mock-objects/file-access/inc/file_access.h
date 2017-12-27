#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H

#include <stdlib.h>

#define FILE_NAME_SIZE 256+1


typedef struct file_access_info FileAccess;

#define FILE_CONTROL_OK           0
#define FILE_CONTROL_FATAL_ERROR -1 
#define FILE_CONTROL_PARAM_ERROR -2
#define FILE_CONTROL_NO_MORE_READ_ERROR -3
#define FILE_CONTROL_NOT_SUPPORT -4

FileAccess* FileAccess_New( );
void FileAccess_Delete( FileAccess** p_file_info );
int FileAccess_Open ( FileAccess* p_file_access ,const char* mode_str, const char* fname );
int FileAccess_Close( FileAccess* p_file_access );
int FileAccess_Write( FileAccess* p_file_access, const unsigned char* buf, unsigned long long size );
int FileAccess_Read ( FileAccess* p_file_access, unsigned char* buf, unsigned char* total_buf, unsigned long long size );
int FileAccess_GetSize ( FileAccess* p_file_access );
int FileAccess_GetTotalReadSize ( FileAccess* p_file_access );
int FileAccess_GetTotalWriteSize( FileAccess* p_file_access );

#endif /* FILE_ACCESS_H */
