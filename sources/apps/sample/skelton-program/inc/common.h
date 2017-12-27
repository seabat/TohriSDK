#ifndef COMMON_H
#define COMMON_H

#include <sys/types.h> /* getpid() */
#include <unistd.h>    /* getpid() */

void log_debug(const char* level, const char* file_name, const char* func_name, int line_no, int pid, const char* format, ...);
void subfunc();
void log_dump( char* buf, int start_index, int end_index );

#ifdef DEBUG
#define LOGD(...) log_debug("D", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGI(...) log_debug("I", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGW(...) log_debug("W", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGE(...) log_debug("E", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#else  /* DEBUG */
#define LOGD(...)
#define LOGI(...) 
#define LOGW(...)
#define LOGE(...) 
#endif /* DEBUG */

#define DUMP( a, b, c ) log_dump( a, b, c )

#endif /* COMMON_H */
