
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void importantRoads(Graph g);

int main(void) {
	Graph g = GraphRead();
	GraphDump(g, stdout);

  printf("Important roads:\n");
  importantRoads(g);
	
	GraphFree(g);
}

