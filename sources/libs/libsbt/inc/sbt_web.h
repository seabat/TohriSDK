#ifndef _SBT_WEB_
#define _SBT_WEB_
/**
 * htmlファイルに含まれる文字列を取得 
 *
 * [引数]
 *  outBuf[OUT] :perse後の文字列
 *  inBuf[IN]   :psrseするHTMLファイルの１行分
 *
 * [戻り値]
 *  なし
 *
 * [制限事項]
 *  inBufはEvernoteでエクスポートしたHTMLファイルの１行分を指定する。
 *  本関数内でoutBufにallocateされるので、本関数を使用する側でそれを開放すること。
 */
void sbt_web_html_parse(char** outBuf,const char* inBuf);

void sbt_web_html_parse_test();

#endif
