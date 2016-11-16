#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<limits.h>
#include<fcntl.h>
#include <unistd.h> 
#include"graph.h"
#define MALLOC(p,s)	p = malloc(s); if(p == NULL) {perror("malloc"); exit(1);}
#define SWAP(a, b, t)  t = a; a = b; b = t;
#define YES 0
#define NO 1
#define CIRCUIT 1
#define NOT_CIRCUIT 0 
int next_permutation(int *a, int n);
void permutate(int *a, int s, int e);
int fd;
void input_graph(graph *gptr){
	int v, i, j;
	printf("Number of vertices: ");
	scanf("%d", &v);
	MALLOC(gptr->am, v * sizeof(int*))
	for(i = 0; i < v; i++) {
		MALLOC(gptr->am[i], v * sizeof(int))}
	gptr->v = v;
	printf("Enter the adjancy matrix of the graph: \n");
	for(i = 0 ; i < v ; i++)
		for(j = 0 ; j < v ; j++) 
			scanf("%d", &(gptr->am[i][j]));
}
void print_graph(graph g) {
	int i, j;
	printf("\nNumber of Vertices : %d\nAdjancy Matrix : \n", g.v);
	for(i = 0; i < g.v; i++) {
		for(j = 0; j < g.v; j++)
			printf("%3d  ", g.am[i][j]);
		putchar('\n');
	}
}
void travelling_salesman(graph g, int m){
	int i, min_cost = INT_MAX, cost, flag, count = 0;
	int *circuit, *min_circuit; 
	MALLOC(circuit, g.v*sizeof(int));
	MALLOC(min_circuit, g.v*sizeof(int));
	for(i = 0; i < g.v; i++) circuit[i] = i;	
	while(next_permutation(circuit + 1 ,g.v - 1) == YES) {
		count++;
		cost = 0;
		flag = CIRCUIT;
		for(i = 1; i < g.v; i++) {
			if(g.am[circuit[i - 1]][circuit[i]] == 0) {
				flag = NOT_CIRCUIT;
				break;
			}
			cost += g.am[circuit[i-1]][circuit[i]];
		}
		if(flag == NOT_CIRCUIT || g.am[0][circuit[i-1]] == 0) {
			flag = NOT_CIRCUIT;
			if(m == 1) { 
				printf("\n\nCount: %d\nNot a circuit.\nPath : ", count);
				for(i = 0; i < g.v ; i++) 	
					printf("->%d", circuit[i] + 1);
			}
		}
		else {
			cost += g.am[0][circuit[i-1]];
			if(m == 1) { 
				printf("\n\nCount: %d\nCost : %d\nPath : ",count, cost);
				for(i = 0; i < g.v ; i++) 	
					printf("->%d", circuit[i] + 1);
				printf("->%d", circuit[0] + 1);
			}
			if(cost < min_cost) {
				min_cost = cost;
				for(i = 0; i < g.v; i++) 
					min_circuit[i] = circuit[i];
			}
		}
	}
	if(min_cost == INT_MAX) {
		printf("\n\nNo travelling path for the salesman :(\n");
		return;
	}
	printf("\n\nMinimum cost : %d\nTravelling Salesman Path : ", min_cost);
	for(i = 0; i < g.v; i++) printf("->%d", min_circuit[i] + 1);
	printf("->%d\n\n", min_circuit[0] + 1);
	free(circuit);
	free(min_circuit);
}
void del_graph(graph *gptr) {
	int i;
	for(i = 0; i < gptr->v; i++) 
		free(gptr->am[i]);
	free(gptr->am);
	remove("perms");
}
int next_permutation(int *a, int n) {
	int c;
	static int flag;
	if(flag == 0) {
		flag = 1;
		fd = creat("perms", 0777);
		if(fd == -1) { perror("create file"); exit(1);}
		permutate(a, 0, n-1);
		close(fd);
		fd = open("perms", O_RDONLY);
	}
	c = read(fd, a, n*sizeof(int));
	if(c < n*sizeof(int))
		return NO;
	return YES;	
}
void permutate(int *a, int s, int e) {
	int i, temp;
	if(s == e)
		write(fd, a, (e+1)*sizeof(int));
	else {
		for(i = s; i <= e; i++) {
			SWAP(a[s], a[i], temp)
			permutate(a, s+1, e);	
			SWAP(a[s], a[i], temp)
		}		
	}
}
