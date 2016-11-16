#include<stdio.h>
#include<string.h>
#include"graph.h"
int main(int argc, char*argv[]) {
	int mode = 0;
	if(argc > 1) mode = 1;
	graph g;
	input_graph(&g);
	print_graph(g);
	travelling_salesman(g, mode);
	del_graph(&g);
	return 0;
}

