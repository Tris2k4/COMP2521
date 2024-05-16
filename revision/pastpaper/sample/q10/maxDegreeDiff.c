
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int maxDegreeDiff(Graph g) {
    // TODO
    int max = -1;
    for (int i = 0; i < g->nV; i++) {
        int outDeg = 0;
        int inDeg = 0;
        struct adjNode *current = g->edges[i];
        while (current) {
            outDeg++;
            current = current->next;
        }

        for (int j = 0; j < g->nV; j++) {
            if (j != i) {
                struct adjNode *current2 = g->edges[j]; 
                    while (current2) {
                        if (current2->v == i) {
                            inDeg++;
                            break;
                        }
                        current2 = current2->next;
                    }
            }
        }
        // printf("%d %d\n", inDeg, outDeg);
        int diff = abs(inDeg - outDeg);
        if (max < diff) {
            max = diff;
        }
    }
    return max;
}