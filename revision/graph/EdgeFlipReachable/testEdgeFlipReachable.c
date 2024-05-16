
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void edgeFlipReachable(Graph g, int src);

int main(void) {
	Graph g = GraphRead();
	GraphDump(g, stdout);
	
	printf("Enter the source vertex: ");
	int src;

	while (scanf("%d", &src) == 1) {
		printf("Reachable from vertex %d:\n", src);
		edgeFlipReachable(g, src);
	  printf("Enter the source vertex: ");
	}
	
	GraphFree(g);
}

