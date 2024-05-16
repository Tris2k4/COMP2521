
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int findTheCrotch(Graph g);

int main(void) {
	Graph g = GraphRead();
	GraphDump(g, stdout);
	
  printf("The crotch is at vertex %d.\n", findTheCrotch(g));
	
	GraphFree(g);
}

