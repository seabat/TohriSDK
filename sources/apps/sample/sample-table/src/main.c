#include <stdio.h>
#include "table.h"

int main(int argc, char const* argv[])
{
	printf("Enter main\n");

	server_main();
	client_main();

	printf("Exit main\n");
	return 0;
}

