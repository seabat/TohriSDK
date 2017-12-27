
#define PLUGIN_MATSU	1
#define PLUGIN_TAKE		2

typedef struct arg_set{
	int  aa;
	char bb;
}arg_set_st;

typedef struct func_pointer{
	void	(*func_a)(int);
	int		(*func_b)(char);
	int		(*func_c)(int,char);
	int		(*func_d)(arg_set_st *);
}func_pointer_st;

typedef struct plugin_info {
	    char*            name;
		func_pointer_st* fp;
}plugin_info_st;

int plugin_manager_main(int type);
void register_func(plugin_info_st* info);
void cps_sub_init();
