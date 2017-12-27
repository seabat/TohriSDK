#include <sys/types.h> /* getpid() */
#include <unistd.h>    /* getpid() */
#include <stdio.h>

#define USE_SBT_LOG_MACRO 1

#define SBT_LOG_FILE "./log.txt"

/**
 * ファイルディスクリプターへログを出力 
 *
 * [説明]
 *  ファイルディスクリプターへログを出力する
 *
 * [引数]
 *  level[IN]     :ログレベル ex."DEBUG","INFO","ERROR"
 *  file_name[IN] :本関数を実装しているファイル名文字列。
 *  func_name[IN] :本関数を実装している関数名文字列。
 *  line_no[IN]   :本関数を実装しているline number。
 *  pid[IN]       :本館数を実行しているスレッドID。
 *  format[IN]    :書式文字列。printf()の第一引数と同じ。
 *  ...[IN]       :可変長引数。printf()の第二引数と同じ。
 *
 * [戻り値]
 *  なし 
 *
 * [制限事項]
 *  file_name,func_name,formatは'\0'を終端とする文字列であること
 *
 * [補足]
 *  クライアントはファイル名を__FILE__で、関数名を__function__で、行番号を__LINE__で、プロセスをgetpid()で取得できる。 
 *  出力の最後に改行文字'\n'をセットする。
 */
void sbt_logln_tofd(FILE* fd, const char* file_name, const char* level, const char* func_name, int line_no, int pid, const char* format, ...);

/**
 * 標準出力へログを出力 
 *
 * [説明]
 *  標準出力へログを出力する
 *
 * [引数]
 *  level[IN]     :ログレベル ex."DEBUG","INFO","ERROR"
 *  file_name[IN] :本関数を実装しているファイル名文字列。
 *  func_name[IN] :本関数を実装している関数名文字列。
 *  line_no[IN]   :本関数を実装しているline number。
 *  pid[IN]       :本館数を実行しているスレッドID。
 *  format[IN]    :書式文字列。printf()の第一引数と同じ。
 *  ...[IN]       :可変長引数。printf()の第二引数と同じ。
 *
 * [戻り値]
 *  なし 
 *
 * [制限事項]
 *  file_name,func_name,formatは'\0'を終端とする文字列であること
 *
 * [補足]
 *  クライアントはファイル名を__FILE__で、関数名を__function__で、行番号を__LINE__で、プロセスをgetpid()で取得できる。 
 *  出力の最後に改行文字'\n'をセットする。
 */
void sbt_logln(const char* level, const char* file_name, const char* func_name, int line_no, int pid, const char* format, ...);

/*
 * ファイルへログを出力 
 *
 * [説明]
 *  ファイルへログを出力する。出力先はマクロSBT_LOG_FILEに設定する。
 *
 * [引数]
 *  level[IN]     :ログレベル ex."DEBUG","INFO","ERROR"
 *  file_name[IN] :本関数を実装しているファイル名文字列。
 *  func_name[IN] :本関数を実装している関数名文字列。
 *  line_no[IN]   :本関数を実装しているline number。
 *  pid[IN]       :本館数を実行しているスレッドID。
 *  format[IN]    :書式文字列。printf()の第一引数と同じ。
 *  ...[IN]       :可変長引数。printf()の第二引数と同じ。
 *
 * [戻り値]
 *  なし 
 *
 * [制限事項]
 *  ログファイルを指定したい場合は、あらかじめ、sbt_flog_init()を実行しておくこと。
 *  function,formatは'\0'を終端とする文字列であること
 *
 * [補足]
 *  クライアントはファイル名を__FILE__で、関数名を__function__で、行番号を__LINE__で、プロセスをgetpid()で取得できる。 
 *  出力の最後に改行文字'\n'をセットする。
 */
void sbt_flogln(const char* level, const char* file_name, const char* func_name, int line_no, int pid, const char* format, ...);

/*
 * ログファイルを初期化
 *
 * [説明]
 *  ログファイルを初期化する。
 *  本館数で設定したファイルパスに対しsbt_flog()でログを出力する 
 *
 * [引数]
 *  path[IN] :ログファイルのパス。
 *
 * [戻り値]
 *  なし 
 *
 * [制限事項]
 *  pathは'\0'を終端とする文字列であること
 */
void sbt_flog_init(const char* path);

void sbt_test_log();

void sbt_dumpln( const unsigned char* buf, int start_index, int end_index );
void sbt_dump( const unsigned char* buf, int start_index, int end_index );


void sbt_mem_dump( void* ptr, unsigned long long num);
void sbt_test_mem_dump();

#define sbt_logln(level,func_name,line_no,pid,format, ...) sbt_logln_tofd(stderr,level,func_name,line_no,pid,format, __VA_ARGS__)

#ifdef USE_SBT_LOG_MACRO
#define SBT_LOG_FD stderr
#define LOGD(...) sbt_logln_tofd(SBT_LOG_FD, "D", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGI(...) sbt_logln_tofd(SBT_LOG_FD, "I", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGW(...) sbt_logln_tofd(SBT_LOG_FD, "W", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define LOGE(...) sbt_logln_tofd(SBT_LOG_FD, "E", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)


#define FLOGD(...) sbt_flogln("D", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define FLOGI(...) sbt_flogln("I", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define FLOGW(...) sbt_flogln("W", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define FLOGE(...) sbt_flogln("E", __FILE__, __func__, __LINE__, getpid(), __VA_ARGS__)
#define FLOG_INIT(a) sbt_flog_init(a)

#define DUMP( a, b, c ) sbt_dump( a, b, c )
#define DUMP_LN( a, b, c ) sbt_dumpln( a, b, c )
#endif /* USE_SBT_LOG_MACRO */
