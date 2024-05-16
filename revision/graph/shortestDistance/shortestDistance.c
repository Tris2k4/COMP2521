
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
	// TODO
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
	int *dist = calloc(GraphNumVertices(g), sizeof(int));
	Queue q = QueueNew();
	
	QueueEnqueue(q, src);
	visited[src] = true;

	dist[src] = 0;

	while (!QueueIsEmpty(q)) {
		int v = QueueDequeue(q);

		for (int w = 0; w < GraphNumVertices(g); w++) {
			if (GraphIsAdjacent(g, v, w) && !visited[w]) {
				visited[w] = true;
				dist[w] = dist[v] + 1;
				QueueEnqueue(q, w);
			}
		}
	}

	if (!visited[dest]) {
		free(visited);
		QueueFree(q);
		free(dist);
		return -1;
	}
	
	int finalDist = dist[dest];
	free(visited);
	QueueFree(q);
	free(dist);
	return finalDist;
}

