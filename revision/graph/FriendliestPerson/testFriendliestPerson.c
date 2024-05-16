
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

double friendliestPerson(Graph g, int p);

int main(void) {
	Graph g = GraphRead();
	GraphDump(g, stdout);
	
	for (int i = 0; i < GraphNumVertices(g); i++) {
    printf("Friendliness of %d: %lf\n", i, friendliestPerson(g, i));
  }
	
	GraphFree(g);
}

