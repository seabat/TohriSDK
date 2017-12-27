#ifndef _SBT_ALLOC_
#define _SBT_ALLOC_

#define SBT_ALLOC_ALLOCATE_NUM 1000
#define SBT_ALLOC_DBG          1

/*--------------------------------------*/
/* Allocate heap area                   */
/*--------------------------------------*/
/**
 * Heapサイズ計算機能付きmalloc 
 *
 * [内容]
 *  標準関数malloc()のラッパー関数。
 *  引数に設定されたサイズをHeapの合計に加算する。
 *  Heapサイズをsbt_alloc.cのg_sbt_all_alloc_sizeに加算する。
 *  Heapのアドレスおよびサイズのセットをsbt_alloc.cのg_allocate_adrs[]にセットする。
 *  g_sbt_all_alloc_sizeおよびg_allocate_adrs[]は本関数を初めて使用する際に初期される。
 *  g_allocate_adrs[]の要素数はdefine値SBT_ALLOC_ALLOCATE_NUMに依存する。
 *
 * [引数]
 *  size :Heapサイズ
 *
 * [制限事項]
 *  本関数でHeapを取得した場合は、sbt_free()で開放処理を行うこと
 */
void* sbt_malloc(size_t size);

/**
 * Heapサイズ計算機能付きfree 
 *
 * [内容]
 *  標準関数free()のラッパー関数。
 *  引数に設定されたアドレスが割り当てられているHeapサイズをHeapの合計から減算する。
 *  freeしたサイズをsbt_alloc.cのG変数g_sbt_all_alloc_sizeから減算する。
 *  freeしたアドレスのG変数g_allocate_adrs[]を削除する。
 *
 * [引数]
 *  size :Heapサイズ
 *
 * [制限事項]
 *  本関数でHeapを開放するHeapは、sbt_malloc()で取得済みであること
 */
void  sbt_free(void *ptr);

/**
 * freeされていないHeap情報をログ出力 
 *
 * [内容]
 *  sbt_malloc()で取得したheapのうち、未開放の情報をログ出力。
 *  g_allocate_adrs[].addr, g_allocate_adrs[].sizeをログ出力。
 *
 * [引数]
 *  なし 
 *
 * [戻り値]
 *  なし
 *
 * [制限事項]
 *  なし
 */
void sbt_alloc_print_remnants();

/**
 * Heapの合計サイズを取得 
 *
 * [内容]
 *  sbt_malloc()で取得したheapのうち、未開放サイズを取得
 *  sbt_alloc.cのG変数g_sbt_all_alloc_sizeの値をリターン。
 *
 * [引数]
 *  ptr[IN]:開放するアドレス 
 *
 * [戻り値]
 *  なし
 *
 * [制限事項]
 *  なし
 */
int sbt_alloc_get_allocate_size();

void  sbt_alloc_test();

#endif
