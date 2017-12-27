#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h> /* getpid() */
#include <unistd.h>    /* getpid() */
#include "common.h"


#define FEATURE_EXECUTE_JOIN

/*
 * 本プログラムはthreadのサンプルプログラム
 * 
 * 1. プロセスIDはgitpid()で取得
 * 2. スレッドIDはpthread_self()で取得
 * 3. LinuxコマンドをCで実行で実行するにはsystem()
 * 4. 仮想メモリ(heap memory)のサイズを取得するLinuxコマンドはgrep VmSize /proc/%d/status
 * 5. 「pthread_createで作ったスレッドはdetachしない限りはjoinしないとスタックなどのリソースが 解放されない。
 *      従ってjoinするのを忘れるとメモリリークを起こす」
 * 6. 「5.」を証明するため、スレッドのメモリリークを起こすには、FEATURE_EXECUTE_JOINを無効化する。
 *    ※サブスレッド処理を先に終了させるため、mainスレッドはsleep()する。
 * 7.  cygwinだとjoinをしない場合にメモリリークが発生しない。Ubuntuだと発生。
*/

void* sub_thread_void(){
	char sub_buf[1024]={0x00};
	pthread_t tid = pthread_self();

	LOGD("%s(0x%x): start thread TID=%p\n", __func__, getpid(), tid );
	sleep(1);
	LOGD("%s(0x%x): end thread   TID=%p\n", __func__, getpid(), tid );
	return NULL;
}

void* sub_thread_int( int* thread_no ){
	char sub_buf[1024]={0x00};
	pthread_t tid = pthread_self();

	LOGD("%s(0x%x): start thread(no=%d) TID=%p\n", __func__, getpid(), *thread_no, tid );
	sleep(1);
	LOGD("%s(0x%x): end thread TID=%p\n", __func__, getpid(), tid );
	return NULL;
}

void create_thread( int thread_no ){
    pthread_t      thread;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 64 * 1024);

	if(1==thread_no%2){
		pthread_create( &thread, NULL, sub_thread_void, (void*)NULL );
	}else{
		pthread_create( &thread, NULL, (void*)sub_thread_int, (void*)&thread_no );
	}

#ifdef FEATURE_EXECUTE_JOIN
	LOGD("%s(0x%x): Wait   main thread\n",__func__, getpid());
	pthread_join( thread, NULL );
	LOGD("%s(0x%x): Resume main thread\n",__func__, getpid());
#else
	LOGD("%s(0x%x): Start sleep  main thread\n",__func__, getpid());
	sleep(3);
	LOGD("%s(0x%x): Stop  sleep  main thread\n",__func__, getpid());
#endif
	pthread_attr_destroy(&attr);
}

int main(int argc, char **argv)
{
	int ret = 0;
	char cmd_buf[50] = {0x00};
	int i;

	LOGD("%s(0x%x): start\n", __func__, getpid());

	LOGD( cmd_buf, "grep VmSize /proc/%d/status", getpid() );
	LOGD("%s(0x%x): Dump virtual memory\n", __func__, getpid());
	system( cmd_buf );

	for(i=0; i<3; ++i){
		create_thread(i+1);
		system( cmd_buf );
	}

exit:
	LOGD("%s(0x%x): end\n", __func__, getpid());
	return ret;
}

