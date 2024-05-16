
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void depthFirstSearchHelper(Graph g, int v, bool *visited) {
	visited[v] = true;

	printf("%d ", v);
	for (int w = 0; w < GraphNumVertices(g); w++) {
		if (v == w) {
			continue;
		}
		if (GraphIsAdjacent(g, v, w) && !visited[w]) {
			depthFirstSearchHelper(g, w, visited);
		}
	}
}

void depthFirstSearch(Graph g, int src) {
	// TODO
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
	depthFirstSearchHelper(g, src, visited);
	free(visited);
}

