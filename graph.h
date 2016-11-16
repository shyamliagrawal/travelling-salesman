typedef struct {
	int v;
	int **am;
}graph;
void input_graph(graph *gptr);
void print_graph(graph g);
void travelling_salesman(graph g, int);
void del_graph(graph *gptr);
