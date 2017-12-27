#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "plugin.h"

#define DEBUG

#ifdef DEBUG
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

#define PLUGIN_MATSU_PATH	"./plugin_dynamic_matsu.so"
#define PLUGIN_TAKE_PATH	"./plugin_dynamic_take.so"

#define PLUGIN_NUM 2

/* 1. The plugin manager don't include header file of dynamic library. 
 * 2. manager
 *    1. Load a dynamic library to memory with function of "dlopen()".
 *    2. Get a pointer, function of "plugin_init()" with function of "dlsym()".
 *    3. Get a list function pointers with functon of "plugin_init()" .
 */


plugin_manage_st g_plugin_manage[PLUGIN_NUM];


plugin_manage_st load_plugin(char* name, int mode){
	void*            handle = NULL;
	plugin_info_st* (*function)(char*); /* plugin_info_st* plugin_init();  */
	plugin_manage_st plugin = {0x00};

	PRINT("%s %s -- start\n",__FILE__,__func__);
	handle = (void*)dlopen( name, mode );
	if(!handle){
		fprintf(stderr, "%s\n",dlerror());
		return plugin;
	}

	function = dlsym(handle, "plugin_init");
	if( NULL==function ){
		fprintf(stderr, "%s\n", dlerror());
		return plugin;
	}

	plugin.p_plugin_info = (*function)(NULL); 
	plugin.p_plugin_handle = handle;

	PRINT("%s %s -- end\n",__FILE__,__func__);
	return plugin; 
}

int unload_plugin(void* handle){
	int (*function)(char*); /* void  plugin_desc(); */

	PRINT("%s %s -- start\n",__FILE__,__func__);
	function = dlsym(handle, "plugin_desc");
	if( NULL==function ){
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
	(*function)(NULL);

	dlclose(handle);
	PRINT("%s %s -- end\n",__FILE__,__func__);
	return 0;
}

int plugin_manager_main(){ 
	PRINT("%s %s -- start\n",__FILE__,__func__);
	/* load plugin */
	g_plugin_manage[0] = load_plugin(PLUGIN_MATSU_PATH, RTLD_LAZY);
	g_plugin_manage[1] = load_plugin(PLUGIN_TAKE_PATH, RTLD_LAZY);

	/* call function in plugin */
	g_plugin_manage[0].p_plugin_info->fp.func_a(1);
	g_plugin_manage[1].p_plugin_info->fp.func_a(1);

	/* unload plugin */
	unload_plugin(g_plugin_manage[0].p_plugin_handle);
	unload_plugin(g_plugin_manage[1].p_plugin_handle);
	PRINT("%s %s -- end\n",__FILE__,__func__);

	return 0;
}


