#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "sbt_log.h"
#include "sbt_file.h"

int get_file_num(const char* dir_name){
	int DBG      = 0;
	int i        = 0;
	int file_num = 0;
	DIR* dir;
	struct dirent* dp;

	dir=opendir(dir_name);

	if ( NULL==dir ){
		LOGD("ディレクトリを開けませんでした");
		return -1;
	}

	for( i=0; NULL!=(dp = readdir(dir)); i++ ){
		if( ( 0 !=strcmp(".",dp->d_name) ) &&
			( 0 !=strcmp( "..", dp->d_name) ) &&
			('.'!=dp->d_name[0]) ){
				if(DBG)LOGD( "%d:%s" , i , dp->d_name );
				file_num++;
		}
	}

	closedir(dir);

	return file_num;
}

int get_file_name_list(const char* dir_name, files_st* p_file_list){
	int DBG        = 0;
	int i          = 0;
	int file_index = 0;
	DIR* dir;
	struct dirent* dp;

	dir=opendir(dir_name);
	if ( NULL==dir ){
		LOGD("ディレクトリを開けませんでした");
		return -1;
	}

	file_index = 0;
	for( i=0; NULL!=(dp = readdir(dir)); i++ ){
		if( ( 0 !=strcmp(".",dp->d_name) ) &&
			( 0 !=strcmp("..",dp->d_name) ) && 
			('.'!=dp->d_name[0]) ){
				strncpy( p_file_list[file_index].name, dir_name, strlen(dir_name) );
				strcat(  p_file_list[file_index].name, "/" );
				strcat(  p_file_list[file_index].name, dp->d_name );
				if(DBG)LOGD( "%d:file name=%s" , file_index , p_file_list[file_index].name );
				file_index++;
		}
	}

	closedir(dir);

	return 0;
}

void sbt_file_test(){

	int       file_num = 0;
	files_st* p_file_list;
	int i;

	file_num = get_file_num("src/");
	p_file_list = (files_st*)malloc( sizeof(files_st)*file_num );
	get_file_name_list( "src/", p_file_list );
	for( i=0;i<file_num;i++ ){
		LOGD( "file name=%s", p_file_list[i].name );
	}
}

