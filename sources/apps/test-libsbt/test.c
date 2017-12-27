#include <stdio.h>

#include "libsbt/sbt_alloc.h"
#include "libsbt/sbt_file.h"
#include "libsbt/sbt_log.h"
#include "libsbt/sbt_string.h"
#include "libsbt/sbt_thread.h"
#include "libsbt/sbt_androidxml.h"
#include "libsbt/sbt_web.h"

int main(int argc, char **argv){

	LOGD("Start");

	LOGD("Start sbt_test_log");
	sbt_test_log();
	LOGD("End sbt_test_log");

	LOGD("Start sbt_alloc_test");
	sbt_alloc_test();
	LOGD("End sbt_alloc_test");

	LOGD("Start sbt_file_log");
	sbt_file_test();
	LOGD("End sbt_file_log");

	LOGD("Start sbt_string_test");
	sbt_string_test();
	LOGD("End sbt_string_test");

	LOGD("Start sbt_test_mem_dump");
	sbt_test_mem_dump();
	LOGD("End sbt_test_mem_dump");

	LOGD("Start sbt_androidxml_test");
    test_sbt_androidxml();
	LOGD("End sbt_androidxml_test");

	LOGD("Start sbt_thread_test");
	sbt_thread_test_join();
	sbt_thread_test_exclusive();
	sbt_thread_test_detatch();
	LOGD("End sbt_thread_test");

	LOGD("Exit");

	return 1;
}
