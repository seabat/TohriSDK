#ifndef FILE_ACCESS_IMPL_H
#define FILE_ACCESS_IMPL_H

typedef struct file_struct{
    FILE*              fp;
	unsigned long long size; 
	unsigned long long total_read_size; 
	unsigned long long total_write_size; 
	char               fname[FILE_NAME_SIZE];
}file_st;

/* モード	ファイル	機能					ファイルがないとき 
 * "r"		テキスト	読み取り				エラー
 * "w"		テキスト	書き込み				新規作成
 * "a"		テキスト	追加書き込み			新規作成
 * "rb"		バイナリ	読み取り				エラー
 * "wb"		バイナリ	書き込み				新規作成
 * "ab"		バイナリ	追加書き込み			新規作成
 * "r+"		テキスト	読み取り及び書き込み	エラー
 * "w+"		テキスト	読み取り及び書き込み	新規作成
 * "a+"		テキスト	追加書き込み			新規作成
 * "rb+"	バイナリ	読み取り及び書き込み	エラー
 * "wb+"	バイナリ	読み取り及び書き込み	新規作成
 * "ab+"	バイナリ	追加書き込み			新規作成
 */

/* "typedef int (*FUNCPTR)(int a,int b);" を定義しておくと
 * "FUNCPTR"を型として使用できる。
 * 例：
 *
 *	typedef int	(*FP_SAMPLE_TYPE)(int a);
 *	
 *	int funcB(int a){
 *		return a;
 *	}
 *
 * 	void funcA(){
 * 		int ret;
 *		FP_SAMPLE_TYPE sample;
 *		sample = funcB();
 *		ret = sample(1);
 *	}
 */
typedef int	(*FP_OPEN_TYPE)(file_st** fst, const char* mode_str, const char* fname);
typedef int	(*FP_CLOSE_TYPE)(file_st* fst);
typedef int	(*FP_WRITE_TYPE)(file_st* fst, const unsigned char* buf, unsigned long long size);
typedef int	(*FP_READ_TYPE)(file_st* fst, unsigned char* buf, unsigned char* total_buf, unsigned long long size);
typedef int	(*FP_GET_SIZE_TYPE)(file_st* fst);
typedef int	(*FP_GET_TOTAL_READ_TYPE)(file_st* fst);
typedef int	(*FP_GET_TOTAL_WRITE_TYPE)(file_st* fst);
typedef int	(*FP_MKDIR_TYPE)(const char* base_dir, const char* add_dir);

int openEx(file_st** fst, const char* mode_str, const char* fname);
int closeEx(file_st* fst);
int writeEx(file_st* fst, const unsigned char* buf, unsigned long long size);
int readEx(file_st* fst, unsigned char* buf, unsigned char* total_buf, unsigned long long size);
int mkdirEx(const char* base_dir, const char* add_dir);
int get_size(file_st* fst);
int get_total_read_size(file_st* fst);
int get_total_write_size(file_st* fst);

#endif /* FILE_ACCESS_IMPL_H */
