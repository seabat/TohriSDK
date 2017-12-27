#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plugin.h"

#if DEBUG
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

/* argument 1 */
#define MATSU		'm'
#define TAKE		't'

int main(int argc, char **argv)
{
	int type = 0;

	PRINT("%s -- start\n",__func__);

	if(1==argc){
		PRINT("no arg\n");
		goto exit;
	}

	if ( *argv[1] == MATSU ) {
		type = PLUGIN_MATSU;
	} else if ( *argv[1] == TAKE ) {
		type = PLUGIN_TAKE;
	}

	plugin_manager_main(type);
exit:
	PRINT("%s -- end\n",__func__);
	return 0;
}
