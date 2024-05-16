
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

bool dfsCycleFound(Graph g, int v, int prev, bool *visited, int *cycleVertex)
{
	visited[v] = true;
	for (int w = 0; w < GraphNumVertices(g); w++)
	{
		if (w == prev)
		{
			continue;
		}
		if (GraphIsAdjacent(g, v, w) && visited[w])
		{
			*cycleVertex = w;
			return true;
		}
		if (GraphIsAdjacent(g, v, w) && !visited[w] && dfsCycleFound(g, w, v, visited, cycleVertex))
		{
			return true;
		}
	}
	return false;
}

void dfsCycle(Graph g, int src, bool *visited, int *cycleVertex)
{
	for (int i = 0; i < GraphNumVertices(g); i++)
	{
		if (dfsCycleFound(g, src, src, visited, cycleVertex))
		{
			return;
		}
	}
}

int findTheCrotch(Graph g)
{
	// todo
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));

	int cycleVertex = -1;
	dfsCycle(g, 0, visited, &cycleVertex);

	for (int i = 0; i < GraphNumVertices(g); i++)
	{
		visited[i] = false;
	}

	for (int i = 0; i < GraphNumVertices(g); i++)
	{
		if (GraphIsAdjacent(g, cycleVertex, i))
		{
			visited[i] = true;
		}
	}

	int crotch = -1;
	int *deg3 = calloc(GraphNumVertices(g), sizeof(int));
	int stored = 0;

	for (int i = 0; i < GraphNumVertices(g); i++)
	{
		int degree = 0;
		for (int j = 0; j < GraphNumVertices(g); j++)
		{
			if (GraphIsAdjacent(g, i, j))
			{
				degree++;
			}
		}
		if (degree == 3)
		{
			deg3[stored++] = i;
		}
	}

	for (int i = 0; i < stored; i++)
	{
		if (!GraphIsAdjacent(g, deg3[i], cycleVertex))
		{
			crotch = deg3[i];
		}
	}

	free(visited);
	free(deg3);

	return crotch;
}
