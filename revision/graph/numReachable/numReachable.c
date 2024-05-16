
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int numReachableHelper(Graph g, int v, int *numReachable, bool *visited) {
	visited[v] = true;
	*numReachable += 1;

	for (int w = 0; w < GraphNumVertices(g); w++) {
		if (GraphIsAdjacent(g, v, w) && !visited[w]) {
			numReachableHelper(g, w, numReachable, visited);
		}
	}
	return *numReachable;
}
int numReachable(Graph g, int src) {
	// TODO
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
	int reachable = 0;
	int res = numReachableHelper(g, src, &reachable, visited);
	free(visited);
	return res;
}

