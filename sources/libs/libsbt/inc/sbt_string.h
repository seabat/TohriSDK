#ifndef _SBT_STRING_
#define _SBT_STRING_

/**
 * SBT_USE_CUSTUM_ALLOC
 *
 * [説明]
 *  本defineが有効である場合、sbt_string.c内ではsbt_malloc()でHEAPが取得される。
 */
#define SBT_USE_CUSTUM_ALLOC

/*--------------------------------------*/
/*  Replace string                      */
/*--------------------------------------*/
/**
 *  置換後の文字列Lenght取得
 *
 * [説明]
 *  第１引数の文字列の置換後の文字列長を計算する
 *
 * [引数]
 *  buf[IN] :全体の文字列
 *  str1[IN]:被置換文字列
 *  str2[IN]:置換文字列
 *
 * [戻り値]
 *  -1    :Length取得失敗
 *  -1以外:第１引数の文字列の置換後文字列長
 *
 * [制限事項]
 *  buf,str1,str2は'\0'を終端とする文字列であること
 */
int sbt_string_get_strchg_len(const char *buf, const char* before_str, const char* after_str);

/**
 *  文字列置換
 *
 * [説明]
 *  第１引数の文字列を置換する
 *
 * [引数]
 *  chg_buf[OUT]  :置換後の文字列
 *  src_buf[IN]   :全体の文字列
 *  before_str[IN]:被置換文字列
 *  after_str[IN] :置換文字列
 *
 * [戻り値]
 *  -1:置換失敗
 *  0 :置換成功
 *
 * [制限事項]
 *  src_buf,befor_str,after_strは'\0'を終端とする文字列であること。
 *  src_bufのlengthが1024以下であること。
 *  本関数内でchg_bufにallocateされるので、本関数を使用する側でそれを開放すること。
 */
int sbt_string_strchg(char** chg_buf, char *buf, const char *before_str, const char *after_str);

/**
 *  文字列分割
 *
 * [説明]
 *  第3引数の文字列src_dataを第5引数のtokenで分割し、第1引数のsplit_str_listにセットする。
 *  第3引数は\0を終端とする文字列でなくてもよい。
 *  token_srr[]=" "の分割文字は' 'と'\n'となる。
 *
 * [引数]
 *  split_str_list[OUT]  :分割文字列のリスト。char* の配列。
 *                        配列の領域は本関数のコール元で確保する。
 *                        src_dataのポインタのリスト。
 *  list_num[IN]         :split_str_list[]の要素数。
 *  src_data[IN]         :全体の文字列。関数内でデータが変更される。tokenが\0で置換される。
 *  src_size[IN]         :全体文字列のサイズ。(最後尾の\0を含むサイズ）
 *  token_str[IN]        :token。文字列として指定する。複数して可能。ex. " ", " \n"
 *
 * [戻り値]
 *  分割数 
 *
 * [制限事項]
 *  tokenは文字列で指定すること。文字列内の文字をtokenとして使用し、文字列で分割することはできない。
 *  src_dataは分割箇所が\0で上書きされる。
 *  分割できる最大数は100。最大値はdefineで指定されている。
 */
int sbt_string_split( char** split_str_list, 
					  int    list_num,
					  char*  src_data, 
					  unsigned long long src_size, 
					  const char* token_str );

void sbt_string_test();

#endif
