#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plugin.h"
#include "plugin_matsu.h"

#define DEBUG

#ifdef DEBUG
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

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
	.func_a	= matsu_a,
	.func_b	= matsu_b,
	.func_c	= matsu_c,
	.func_d	= matsu_d,
};

void plugin_matsu_init(){
	plugin_info_st info;

	info.name = MATSU;
	info.fp   = &fp;
	register_func(&info);
}
