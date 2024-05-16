
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int diameter(Graph g);

int main(void) {
	Graph g = GraphRead();
	GraphDump(g, stdout);

  printf("Diameter: %d\n", diameter(g));

	
	GraphFree(g);
}

