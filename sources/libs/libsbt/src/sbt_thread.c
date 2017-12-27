
#include "sbt_log.h"
#include <pthread.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct _test_thread_func_st{
	int   size; 
	char  buf[4];
}test_thread_func_st;

#if 0
typedef	void (*thread_func)(void* arg);
typedef struct _thread_func_st{
	thread_func func;
//	void*      func;
	void*      f_arg; 
}thread_func_st;
#endif

void sbt_thread_detatch( ){
	pthread_detach(pthread_self());
}

void sbt_thread_exit( ){
	pthread_exit(NULL); /* For sbt_thread */
}

static void *sub_thread_detach(test_thread_func_st* param){
	int i;
	pthread_t tid = pthread_self();

	LOGD("Start(threadID=0x%x)", tid );
	LOGD("param->size=%d", param->size );
	for( i=0; i<param->size; i++ ){
        sleep(1);
        LOGI("param->buf[%d]=%d", i, param->buf[i] );
	}

	LOGD("End(threadID=0x%x)", tid);
	sbt_thread_detatch();
	return NULL;
}

static void *sub_thread_join(int* param){
	int i;
	pthread_t tid = pthread_self();

	LOGD("Start(threadID=0x%x)", tid );

	for( i=0; i<*param; i++ ){
        sleep(1);
        LOGI("count = %d" , i);
	}

	LOGD("End(threadID=0x%x)", tid);
	return NULL;
}

static void *test_sleep_func(){
	pthread_t tid = pthread_self();

	LOGD("Start(threadID=0x%x)", tid );

    sleep(1);

	LOGD("End(threadID=0x%x)", tid);
	return NULL;
}

pthread_mutex_t test_mutex;

static void *sub_thread_exclusive(int* param){
	pthread_t tid = pthread_self();

	LOGD("Start(param=0x%x threadID=0x%x)", *param, tid );

    pthread_mutex_lock(&test_mutex);
    test_sleep_func();
    pthread_mutex_unlock(&test_mutex);

	LOGD("End(threadID=0x%x)", tid);
	return NULL;
}

#if 0
static void *detach_thread_func(thread_func_st* param){
	sleep(1);
	LOGD("Start" );
	param->func(param->f_arg);
	LOGD("End" );
	return NULL;
}
#endif 

void sbt_thread_run( const void* func, const void* f_arg, short int join_flg, long int stk_size){
    pthread_t       thread;
	pthread_attr_t  attr;

	pthread_attr_init(&attr);

	/* Set a stack size at a new thread */
	if(0==stk_size){
		pthread_attr_setstacksize( &attr, 64 * 1024 );
	}else{
		pthread_attr_setstacksize( &attr, stk_size );
	}

	/* Set joinable or detach to attr */
	if(1==join_flg){
		pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
	}else{
		pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
	}

	/* Create a new thread */
	pthread_create( &thread, &attr, (void*)func, (void*)f_arg );

	if(1==join_flg){
//		LOGD("Wait for sub thread");
		pthread_join( thread, NULL );
//		LOGD("Resume main thread");
	}

	pthread_attr_destroy(&attr);
	return;
}


int sbt_thread_test_join(){

	int        loop_cnt = 6;
	pthread_t  tid = pthread_self();

	LOGD( "Start (main threadID=0x%x)", tid );
	sbt_thread_run( (const void*)sub_thread_join, 
					(const void*)&loop_cnt , 
					1,  /* joinable */
					0);

	LOGD( "End (main threadID=0x%x)", tid );

	return 0;
}

int sbt_thread_test_detatch(){

	test_thread_func_st* st_thread_func = NULL;
	pthread_t       tid = pthread_self();

	LOGD( "Start (main threadID=0x%x)", tid );
    st_thread_func = (test_thread_func_st*)malloc( sizeof(test_thread_func_st) );
	st_thread_func->size = 4;
	st_thread_func->buf[0] = 1;
	st_thread_func->buf[1] = 2;
	st_thread_func->buf[2] = 3;
	st_thread_func->buf[3] = 4;
	sbt_thread_run( (const void*)sub_thread_detach, 
					(const void*)st_thread_func, 
					0, /* detach */
					0);
	free(st_thread_func);

	LOGD( "End (main threadID=0x%x)", tid );

	sbt_thread_exit(); /* For sbt_thread */

	return 0;
}

int sbt_thread_test_exclusive(){

	int       i   = 0;
	pthread_t tid = pthread_self();

	LOGD( "Start (main threadID=0x%x)", tid );
    for(i=0; i<3; i++){
	    sbt_thread_run( (const void*)sub_thread_exclusive, 
	    				(const void*)&i , 
		    			1,  /* joinable */
		    			0);
    }

	LOGD( "End (main threadID=0x%x)", tid );
	return 0;
}

