#include <string.h>
#include <stdio.h>
#include "common.h"

int main(int argc, char **argv) {

    LOGD("Start");

    char keyword[512]= {0};
    char path[512]= {0};

    if (argc<=1) {
        printf("Please set keyword\n");
        return -1;
    } else {
        strcpy(keyword, argv[1]);
    }

    if (argc<=2) {
        strcpy(path, ".");
    } else {
        strcpy(path, argv[2]);
    }

    scan_dir(keyword, path, 0);

    LOGD("Exit");

    return 0;
}

