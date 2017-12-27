#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plugin.h"

#define DEBUG

#ifdef DEBUG
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

#define  MATSU "plugin-matsu"

static void matsu_a(int ii){
	PRINT("%s -- start\n",__func__);
	PRINT("%s -- exit\n",__func__);
	return;
}

static int matsu_b(char cc){
	PRINT("%s -- start\n",__func__);
	PRINT("%s -- exit\n",__func__);
	return 0;
}

static int matsu_c(int ii, char cc){
	PRINT("%s -- start\n",__func__);
	PRINT("%s -- exit\n",__func__);
	return 0;
}

static int matsu_d(arg_set_st* st){
	PRINT("%s -- start\n",__func__);
	PRINT("%s -- exit\n",__func__);
	return 0;
}


static func_pointer_st fp = {
	.func_a = matsu_a,
	.func_b = matsu_b,
	.func_c = matsu_c,
	.func_d = matsu_d,
};

static plugin_info_st info;

/* plugin_init
 *
 * Get public function pointer and function name in this library.
 * Function prototype of plugin_init in each dynamic libray is same. 
 */
plugin_info_st* plugin_init(){
	PRINT("%s %s -- start\n",__FILE__,__func__);
	PRINT("%s %s -- exit\n",__FILE__,__func__);

	info.name = MATSU;
	info.fp   = fp;
	return &info;
}

/*  plugin_desc
 
 * Exit this libray.
 * Function prototype of plugin_init in each dynamic libray is same. 
 */
void plugin_desc(){
	PRINT("%s %s -- start\n",__FILE__,__func__);
	PRINT("%s %s -- exit\n",__FILE__,__func__);
}

