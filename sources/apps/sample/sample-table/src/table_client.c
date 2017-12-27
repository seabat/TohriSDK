#include <stdio.h>
#include "table.h"

int client_main(){
	stDataTable* pDataTable = NULL;
	stFuncTable* pFuncTable = NULL;
	int dataTableSize = 0;
	int funcTableSize = 0;
    int i =0;

	printf( "Enter client_main\n" );

	getDataTable( &dataTableSize, &pDataTable );

	printf( "pDataTable : value=%p size=%d\n", pDataTable,  (int)sizeof(pDataTable)  );
	printf( "*pDataTable: value=%d size=%d\n", *pDataTable, (int)sizeof(*pDataTable) );

	for( i=0; i < dataTableSize; i++ ){
		printf( "id=%d name=%s\n", pDataTable[i].id, pDataTable[i].name );
	}

	getFuncTable( &funcTableSize, &pFuncTable );

	printf( "pFuncTable : value=%p size=%d\n", pFuncTable,  (int)sizeof(pFuncTable)  );
	printf( "*pFuncTable: value=%d size=%d\n", *pFuncTable, (int)sizeof(*pFuncTable) );

	for( i=0; i < funcTableSize; i++ ){
		printf( "id=%d\n", pFuncTable[i].id );
		pFuncTable[i].func('a');
	}

	printf( "Exit client_main\n" );
	return 0;
}
