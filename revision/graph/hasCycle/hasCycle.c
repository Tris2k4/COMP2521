
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

bool hasCycleHelper(Graph g, int v, int prev, bool *visited) {
	visited[v] = true;

	for (int w = 0; w < GraphNumVertices(g); w++) {
		if (w == prev) {
			continue;
		}
		if (GraphIsAdjacent(g, v, w) && visited[w]) {
			return true;
		}
		if (GraphIsAdjacent(g, v, w) && !visited[w] && hasCycleHelper(g, w, v, visited)) {
			return true;
		}
	}
	return false;
}

bool hasCycle(Graph g) {
	// TODO
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));

	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (!visited[i] && hasCycleHelper(g, i, i, visited)) {
			free(visited);
			return true;
		}
	}
	free(visited);
	return false;
}

