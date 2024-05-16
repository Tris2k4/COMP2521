
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"


int furthestReachable(Graph g, int src) {
	// TODO
	int *dist = calloc(GraphNumVertices(g), sizeof(int));
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
	int *predecessor = calloc(GraphNumVertices(g), sizeof(int));

	for (int i = 0; i < GraphNumVertices(g); i++) {
		predecessor[i] = -1;
	}

	int count = 0;
	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (GraphIsAdjacent(g, src, i)) {
			count++;
		}
	}
	 
	if (count == 0) {
		free(dist);
		free(visited);
		free(predecessor);
		return src;
	}

	Queue q = QueueNew();
	QueueEnqueue(q, src);
	predecessor[src] = -1;
	visited[src] = true;
	dist[src] = 0;

	while (!QueueIsEmpty(q)) {
		int v = QueueDequeue(q);

		for (int w = 0; w < GraphNumVertices(g); w++) {
			if (GraphIsAdjacent(g, v, w) && !visited[w]) {
				predecessor[w] = v;
				dist[w] = dist[v] + 1;
				visited[w] = true;
				QueueEnqueue(q, w);
			}
		}
	}

	int max = -1e9;
	int vertex = -1;
	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (dist[i] >= max) {
			max = dist[i];
			vertex = i;
		}
	}
	free(dist);
	free(visited);
	free(predecessor);
	QueueFree(q);
	return vertex;
}
