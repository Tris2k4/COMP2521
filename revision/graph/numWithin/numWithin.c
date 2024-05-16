
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int numWithin(Graph g, int src, int dist) {
	// TODO
	if (dist == 0) {
		return 1;
	}

	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
	int *distance = calloc(GraphNumVertices(g), sizeof(int));

	int num = 1;
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	visited[src] = true;
	distance[src] = 0;

	while (!QueueIsEmpty(q)) {
		int v = QueueDequeue(q);

		for (int w = 0; w < GraphNumVertices(g); w++) {
			if (GraphIsAdjacent(g, v, w) && !visited[w] && distance[v] + 1 <= dist) {
				distance[w] = distance[v] + 1;
				visited[w] = true;
				num++;
				QueueEnqueue(q, w);
			}
		}
	}
	QueueFree(q);
	free(visited);
	free(distance);
	return num;
}

