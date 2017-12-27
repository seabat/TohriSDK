#include <stdio.h>
#include "table.h"

static stDataTable dataTable[]={ 
	{ 1, "tokyo"  },
	{ 2, "nagoya" },
	{ 3, "osaka"  },
	{ 4, "hakata" },
};

static int func_a(char arg){
	printf("func_a\n");
	return 0;
}

static int func_b(char arg){
	printf("func_b\n");
	return 1;
}

static int func_c(char arg){
	printf("func_c\n");
	return 2;
}

static stFuncTable funcTable[]={ 
	{ 1, func_a },
	{ 2, func_b },
	{ 3, func_c },
};


int server_main()
{
	int  i;

	printf("Enter server_main\n");
	
	/*****************/
	/* simple table  */
	/*****************/
	printf( "size of the data table = %d\n", (int)sizeof(dataTable) );
	printf( "count entries in the data table = %d\n", (int)(sizeof(dataTable)/sizeof(stDataTable)) );
	for( i=0; i < sizeof(dataTable)/sizeof(stDataTable); i++ ){
		printf( "id=%d name=%s\n", dataTable[i].id, dataTable[i].name );
	}

	/*****************/
	/* function table  */
	/*****************/
	printf( "size of the function table = %d\n", (int)sizeof(funcTable) );
	printf( "count entries in the function table = %d\n", (int)(sizeof(funcTable)/sizeof(stFuncTable)) );
	for( i=0; i < sizeof(funcTable)/sizeof(stFuncTable); i++ ){
		printf( "id=%d\n", funcTable[i].id );
		funcTable[i].func('a');
	}

	printf("Exit server_main\n");
	return 0;
}

void getDataTable( int* p_size, stDataTable** pp_struct ){
	*p_size = sizeof(dataTable)/sizeof(stDataTable);
	*pp_struct    = dataTable;
}

void getFuncTable( int* p_size, stFuncTable** pp_struct ){
	*p_size = sizeof(funcTable)/sizeof(stFuncTable);
	*pp_struct    = funcTable;
}
