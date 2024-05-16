
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
// include Stack/Queue as needed

void dfs(Graph g, int v, bool *visited) {
    visited[v] = true;
    printf("%d ", v);
    for (int w = 0; w < GraphNumVertices(g); w++) {
        if (GraphIsAdjacent(g, v, w) && !visited[w]) {
            dfs(g, w, visited);
        }
        if (!GraphIsAdjacent(g, v, w) && GraphIsAdjacent(g, w, v) && !visited[w]) {
            dfs(g, w, visited);
        }
    }
}

void edgeFlipReachable(Graph g, int src) {
    int adjacent = 0;
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (GraphIsAdjacent(g, src, i)) {
            adjacent++;
        }
    }
    if (adjacent == 0) {
        printf("%d\n", src);
        return;
    }

    bool *visited = calloc(GraphNumVertices(g), sizeof(bool));

    dfs(g, src, visited);
    free(visited);
    printf("\n");
}
