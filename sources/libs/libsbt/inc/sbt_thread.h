#ifndef _SBT_THREAD_
#define _SBT_THREAD_

/**
 * Run a function on a new thread.<br/>
 *
 * @param func  [IN] A function.
 * @param f_arg [IN] A function's argument.
 * @param join_flg [IN] 0:A detatched thread, 1:A joinable thread
 * @param stk_size [IN] A stack size of a new thread
 * @return None
 * @note   If join_flg is 0, a caller's thread calls thread_exit() </br>
 *         between a time of calling this function and a end of the caller's thread.</br>
 *         If join_flg is 0, a new thread's function calls pthread_detach();</br>
 *         </br>
 *         After a caller's thread calls this function, the caller's thread may free f_arg's area.
 */
void sbt_thread_run( const void* func, const void* f_arg, short int join_flg, long int stk_size);

/**
 * Detatch a current thread.<br/>
 * This is the function wrapped "pthread_detatch()"
 */
void sbt_thread_detatch();

/**
 * Terminate all threads.<br/>
 * This is the function wrapped "pthread_exit()"
 */
void sbt_thread_exit();

int sbt_thread_test_join();
int sbt_thread_test_detatch();
int sbt_thread_test_exclusive();

#endif
