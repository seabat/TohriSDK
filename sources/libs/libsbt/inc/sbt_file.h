
typedef struct files{
	char name[100];
}files_st;

/**
 * ディレクトリ下のファイルの数を取得 
 *
 * [内容]
 *  第１引数に指定されたディレクトリ内のファイル数を取得する。
 *  以下はファイルとしてカウントされない。
 *   「.」から始まるファイル名。
 *
 * [引数]
 *  dr_name[IN]:パス
 *     カレントからの相対パスまたは絶対パス
 *
 * [戻り値]
 *  ファイル数
 *
 * [制限事項]
 *  なし
 */
int get_file_num(const char* dir_name);

/**
 * ディレクトリ下のファイル一覧 
 *
 * [内容]
 *  第１引数に指定されたディレクトリ内のファイ一覧を取得する。
 *  以下はファイル。
 *   「.」から始まるファイル名。
 *
 * [引数]
 *  dr_name[IN]:パス
 *     カレントからの相対パスまたは絶対パス
 *  p_file_list[OUT]:ファイル一覧
 *     
 *
 * [戻り値]
 *  -1:エラー
 *
 * [制限事項]
 *  get_file_num()で取得できるファイル数でp_file_listの領域を確保しておくこと 
 */
int get_file_name_list(const char* dir_name, files_st* list);


void sbt_file_test();
