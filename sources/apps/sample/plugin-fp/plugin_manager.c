#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plugin.h"
#include "plugin_matsu.h"
#include "plugin_take.h"

#define DEBUG

#ifdef DEBUG
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

plugin_info_st g_plugin;

int plugin_manager_main(int type)
{
	int        ret         = 0;
	char       cmd_buf[50] = {0};
	arg_set_st arg_set     = {1, 'a'};
	
	PRINT("%s -- start\n",__func__);

	if ( PLUGIN_MATSU == type ) {
		plugin_matsu_init();
	} else if ( PLUGIN_TAKE == type ) {
		plugin_take_init();
	}

	PRINT( "[%s]", g_plugin.name );

	if ( (fgets(cmd_buf, sizeof(cmd_buf), stdin)) == NULL ) {
		PRINT("input err!\n");
		goto exit;
	}

	cmd_buf[strlen(cmd_buf) - 1] = '\0';

	g_plugin.fp->func_a(1);
	g_plugin.fp->func_b('a');
	g_plugin.fp->func_c(1,'a');
	g_plugin.fp->func_d(&arg_set);
	
exit:
	PRINT("%s -- end\n",__func__);
	return ret;
}

void register_func(plugin_info_st* info){
	g_plugin.name = info->name;
	g_plugin.fp   = info->fp;
}
