
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	// TODO
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
	
	Queue q = QueueNew();
	QueueEnqueue(q, src);

	visited[src] = true;

	while (!QueueIsEmpty(q)) {
		int v = QueueDequeue(q);
		printf("%d ", v);
		for (int w = 0; w < GraphNumVertices(g); w++) {
			if (GraphIsAdjacent(g, v, w) && !visited[w]) {
				visited[w] = true;
				QueueEnqueue(q, w);
			}
		}
	}
	free(visited);
	QueueFree(q);
}

