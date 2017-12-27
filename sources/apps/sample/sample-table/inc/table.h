
typedef struct st_dataTable{
	int  id;
	char name[100];
}stDataTable;

typedef struct st_funcTable{
	int  id;
	int  (*func)(char arg);
}stFuncTable;

void getDataTable( int* p_size, stDataTable** pp_struct );
void getFuncTable( int* p_size, stFuncTable** pp_struct);
int server_main();
int client_main();

