#ifndef LOG_H
#define LOG_H

#include <sys/types.h> /* getpid() */
#include <unistd.h>    /* getpid() */

void log_debug(const char* level, const char* file_name, const char* func_name, int line_no, int pid, const char* format, ...);
void log_dump( unsigned char* buf, int start_index, int end_index );

#define LOGD(...) log_debug("D", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGI(...) log_debug("I", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGW(...) log_debug("W", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGE(...) log_debug("E", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)

#define DUMP( a, b, c ) log_dump( a, b, c )

#endif /* LOG_H */
