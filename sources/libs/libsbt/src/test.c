#include <stdio.h>

#include "sbt_alloc.h"
#include "sbt_file.h"
#include "sbt_log.h"
#include "sbt_string.h"
#include "sbt_web.h"

int main(int argc, char **argv){

	LOGD("Start");

	sbt_test_log();
	sbt_alloc_test();
	sbt_file_test();
	sbt_string_test();

	LOGD("Exit");

	return 1;
}
