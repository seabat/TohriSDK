//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "sbt_log.h"
#include "sbt_alloc.h"

/*--------------------------------------*/
/*  Allocate heap area                  */
/*--------------------------------------*/
typedef struct sbt_alloc{
	void*  addr;
	int    size;
}sbt_alloc_st;
static int g_sbt_all_alloc_size = 0;
static sbt_alloc_st g_allocate_adrs[SBT_ALLOC_ALLOCATE_NUM];

/**
 * Heap管理領域を初期化 
 *
 * [内容]
 *  Heapサイズを0にセット
 *
 * [引数]
 *  なし
 *
 * [制限事項]
 *  なし
 */
static void sbt_malloc_init(){
	memset( g_allocate_adrs, 0x00, sizeof(g_allocate_adrs));
}

void* sbt_malloc(size_t size){
	int i;
	void* adr =NULL;

	adr = (void*)malloc(size);
	if( NULL!=adr ){
		if(0==g_sbt_all_alloc_size){
			sbt_malloc_init();
		}

		for( i=0; i<SBT_ALLOC_ALLOCATE_NUM; i++ ){
			if( NULL == g_allocate_adrs[i].addr ){
				g_sbt_all_alloc_size = g_sbt_all_alloc_size + size;
				if(SBT_ALLOC_DBG) LOGD("Add index=%d and address=0x%p => all size=%d ", i, adr, g_sbt_all_alloc_size);
				g_allocate_adrs[i].addr=(void*)adr;
				g_allocate_adrs[i].size= size;
				break;
			}
		}
	}
	return adr;
}


void sbt_free(void *ptr){
	int i;

	if( NULL!=ptr ){
		for(i=0; i<SBT_ALLOC_ALLOCATE_NUM; i++){
			if(g_allocate_adrs[i].addr==(void*)ptr){
				g_sbt_all_alloc_size = g_sbt_all_alloc_size - g_allocate_adrs[i].size;
				if(SBT_ALLOC_DBG) LOGD("Delete index=%d and address=0x%p => all size=%d", i, ptr ,g_sbt_all_alloc_size);
				memset( &g_allocate_adrs[i], 0x00, sizeof(sbt_alloc_st));
				break;
			}
		}
		free(ptr);
	}
}

void sbt_alloc_print_remnants(){
	int i=0;
	LOGD("Start printing the remant of allocations");
	for(i=0; i<SBT_ALLOC_ALLOCATE_NUM; i++){
		if(NULL != g_allocate_adrs[i].addr){
			LOGD("index=%d address=0x%p size=%d" , i, g_allocate_adrs[i].addr, g_allocate_adrs[i].size);
		}
	}
	LOGD("Terminate printing the remant of allocations");
}

int sbt_alloc_get_allocate_size(){
	return g_sbt_all_alloc_size;
}


void sbt_alloc_test(){
	char* a = NULL;
	char* b = NULL;
	char* c = NULL;

	LOGD("Start sbt_alloc_test");

	/* test case 1 */
	LOGD("test1");
	a = sbt_malloc(50);
	sbt_free(a);
	a = NULL;
	assert( 0 == sbt_alloc_get_allocate_size() );

	/* test case 2 */
	LOGD("test2");
	a = sbt_malloc(30);
	b = sbt_malloc(40);
	sbt_free(a);
	a = NULL;
	sbt_free(b);
	b = NULL;
	assert( 0 == sbt_alloc_get_allocate_size() );

	/* test case 3 */
	LOGD("test3 result1 index=0  size=30");
	LOGD("test3 result2 index=2  size=40");
	a = (char*)sbt_malloc(30);
	b = (char*)sbt_malloc(40);
	c = (char*)sbt_malloc(50);
	sbt_free(b);
	sbt_alloc_print_remnants();

	LOGD("End sbt_alloc_test");
}
