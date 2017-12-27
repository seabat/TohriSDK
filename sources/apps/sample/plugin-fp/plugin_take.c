#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plugin.h"
#include "plugin_take.h"

#define DEBUG

#ifdef DEBUG
#define PRNT(...) printf(__VA_ARGS__)
#else
#define PRNT(...)
#endif


static void take_a(int ii){
	PRNT("%s -- start\n",__func__);
	PRNT("%s -- end\n",__func__);
	return;
}

static int take_b(char cc){
	PRNT("%s -- start\n",__func__);
	PRNT("%s -- end\n",__func__);
	return 0;
}

static int take_c(int ii, char cc){
	PRNT("%s -- start\n",__func__);
	PRNT("%s -- end\n",__func__);
	return 0;
}

static int take_d(arg_set_st* st){
	PRNT("%s -- start\n",__func__);
	PRNT("%s -- end\n",__func__);
	return 0;
}

static func_pointer_st fp = {
	.func_a	= take_a,
	.func_b	= take_b,
	.func_c	= take_c,
	.func_d	= take_d,
};

void plugin_take_init(){
	plugin_info_st info;

	info.name = TAKE;
	info.fp   = &fp;
	register_func(&info);
}
