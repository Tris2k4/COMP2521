#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void dfsStandard(Graph g, bool *visitedStandard, int v, int *dist, Vertex vs[], int *stored) {
    visitedStandard[v] = true;
    for (int w = 0; w < g->nV; w++) {
        if (w == v) {
            continue;
        }

        if (g->stdEdges[v][w] == 1 && !visitedStandard[w] && dist[v] + 1 <= 1) {
            vs[*stored] = w;
            *stored += 1;
            dist[w] = dist[v] + 1;
            dfsStandard(g, visitedStandard, w, dist, vs, stored);
        }
    }
}

bool search(Vertex vs[], int n, Vertex val) {
    for (int i = 0; i < n; i++) {
        if (vs[i] == val) {
            return true;
        }
    }
    return false;
}

void dfsHigh(Graph g, bool *visitedHigh, int v, double *dist, Vertex vs[], int *stored) {
    visitedHigh[v] = true;
    for (int w = 0; w < g->nV; w++) {
        if (w == v) {
            continue;
        }
        if (g->fastEdges[v][w] == 1 && !visitedHigh[w] && dist[v] + 0.5 <= 1) {
            vs[*stored] = w;
            *stored += 1;
            dist[w] = dist[v] + 0.5;
            dfsHigh(g, visitedHigh, w, dist, vs, stored);
        }
    }
}

int dayTrip(Graph g, Vertex s, Vertex vs[]) {
    int stored = 0;

    int *distStandard = calloc(g->nV, sizeof(int));
    double *distHigh = calloc(g->nV, sizeof(double));

    bool *visitedStandard = calloc(g->nV, sizeof(bool));
    bool *visitedHigh = calloc(g->nV, sizeof(bool));

    distStandard[s] = 0;
    distHigh[s] = 0;

    Vertex *temp = calloc(g->nV, sizeof(Vertex));
    dfsStandard(g, visitedStandard, s, distStandard, temp, &stored);
    dfsHigh(g, visitedHigh, s, distHigh, temp, &stored);

    int stored2 = 0;
    for (int i = 0; i < stored; i++) {
        if (temp[i] != 0 && !search(vs, stored2, temp[i])) {
            vs[stored2++] = temp[i];
        }
    }

    free(distStandard);
    free(distHigh);
    free(visitedStandard);
    free(visitedHigh);
    free(temp);

    return stored2;
}
