
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"
// Include ADTS as needed

int diameter(Graph g) {
    int maxDiameter = 0;
    for (int v = 0; v < GraphNumVertices(g); v++) {
        int *dist = calloc(GraphNumVertices(g), sizeof(int));
        bool *visited = calloc(GraphNumVertices(g), sizeof(bool));

        Queue q = QueueNew();
        QueueEnqueue(q, v);
        visited[v] = true;

        while (!QueueIsEmpty(q)) {
            int u = QueueDequeue(q);

            for (int w = 0; w < GraphNumVertices(g); w++) {
                if (GraphIsAdjacent(g, u, w) && !visited[w]) {
                    dist[w] = dist[u] + 1;
                    visited[w] = true;
                    QueueEnqueue(q, w);
                }
            }
        }

        for (int i = 0; i < GraphNumVertices(g); i++) {
            if (dist[i] > maxDiameter) {
                maxDiameter = dist[i];
            }
        }

        free(visited);
        free(dist);
        QueueFree(q);
    }

    return maxDiameter;
}

