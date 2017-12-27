#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <err.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "common.h"

static void scan_file(const char* keyword, const char* file_name){
    FILE*       fp       = NULL;
    char        buf[2048]= {0};
    char*       ret      = NULL;
    unsigned int line    = 0;

//    LOGD( "Enter" );

    /* file open */
    fp = fopen(file_name, "r");
    if(NULL==fp){
        LOGE( "%s", strerror(errno) );
        goto exit;
    }

    while ( fgets(buf, sizeof(buf), fp) != NULL ) {
        line++;
        ret = strstr(buf, keyword);
        if (ret != NULL) {
            if (0 == (ret - buf)) {
                // Check if the searching string starts the beginning of the line 
                printf("%s|%d| %s", file_name, line, buf);
            }
        }
    }

exit:
    if( NULL!=fp ){
        fclose(fp);
    }

//    LOGD( "Exit" );

    return;
}

void scan_dir(const char* keyword, const char *dir_name, int hierarchy) {

    DIR   *dir = NULL;;
    struct dirent *dp = NULL;
    struct stat statbuf;
    int space_num = hierarchy * 2;

    hierarchy++;

    if((dir=opendir(dir_name))==NULL){
        perror("opendir");
        exit(-1);
    }

    chdir(dir_name);

    for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){
        if (strcmp(".", dp->d_name) == 0 || 
            strcmp("..", dp->d_name) == 0) {
            continue;
        }

//        for (int i=0; i<space_num; i++) {
//            printf(" ");
//        }
//        printf("%s\n",dp->d_name);

        lstat(dp->d_name, &statbuf);

        if (S_ISDIR(statbuf.st_mode)) {
            scan_dir(keyword, dp->d_name, hierarchy);
        }

        if (S_ISREG(statbuf.st_mode)) {
            scan_file(keyword, dp->d_name);
        }

    }

    chdir("..");
    closedir(dir);
}


