// Implementation of boulder climbing algorithms

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "Wall.h"
#include "climber.h"

#define ARRAY_SIZE 1e6
// function prototypes
//---------------------------Task 2-----------------------------------------
static struct path shortestPath(Wall w, struct path p, struct rock *rocksSameColour,
                         int numRocksSameColour, int reach);
static bool vSetIsEmpty(bool *vSet, int numRocks);
static int findMinVertex(bool *vSet, int *dist, int numRocks);
static double straightDist(int r1, int c1, int r2, int c2);
//---------------------------Task 3-----------------------------------------
static struct path findMinEnergyPathHelper(struct path p, Wall wall, int reach,
                                    int *energyCosts, struct rock *rocks,
                                    int numRocks);
//---------------------------Task 4-----------------------------------------
static struct path findMinTurnsPathHelper(struct path p, Wall wall, int reach,
                                   int *energyCost, int maxEnergy,
                                   struct rock *rocks, int numRocks);

//-------------------------------------------------------------------------------

struct path findShortestPath(Wall w, int reach, Colour colour)
{
    // TODO - Task 2
    struct rock *rocksArray = calloc(WallNumRocks(w), sizeof(struct rock));
    int numRocks = WallGetAllRocks(w, rocksArray);

    int numRocksSameColour = 0;

    for (int i = 0; i < numRocks; i++)
    {
        if (WallGetRockColour(w, rocksArray[i].row, rocksArray[i].col) == colour)
        {
            numRocksSameColour++;
        }
    }

    // put all the rocks have same colour in another array

    struct rock *rocksSameColour =
        calloc(numRocksSameColour, sizeof(struct rock));

    // Initialize an index for rocksSameColour array
    int rocksSameColourIndex = 0;

    // Iterate over all rocks and add those with the specified color to
    // rocksSameColour
    for (int i = 0; i < numRocks; i++)
    {
        if (WallGetRockColour(w, rocksArray[i].row, rocksArray[i].col) == colour)
        {
            rocksSameColour[rocksSameColourIndex++] = rocksArray[i];
        }
    }

    // check if there is no starting point
    int numStartPoints = 0;
    for (int i = 0; i < numRocksSameColour; i++)
    {
        if (rocksSameColour[i].row <= reach)
        {
            numStartPoints++;
        }
    }

    // if there is no starting point then return no path;
    if (numStartPoints == 0)
    {
        free(rocksArray);
        free(rocksSameColour);
        return (struct path){0, NULL};
    }

    struct path p = {0, p.rocks = calloc(ARRAY_SIZE, sizeof(struct rock))};
    free(rocksArray);
    return shortestPath(w, p, rocksSameColour, numRocksSameColour, reach);
}

static struct path shortestPath(Wall w, struct path p, struct rock *rocksSameColour,
                         int numRocksSameColour, int reach)
{
    int *dist = malloc(sizeof(int) * numRocksSameColour);
    int *predecessor = malloc(sizeof(int) * numRocksSameColour);
    bool *vSet = malloc(sizeof(bool) * numRocksSameColour);
    int *numRocksClimbed = malloc(sizeof(int) * numRocksSameColour);

    if (!dist || !predecessor || !vSet || !numRocksClimbed)
    {
        free(dist);
        free(predecessor);
        free(vSet);
        free(numRocksClimbed);
        return (struct path){0, NULL};
    }

    for (int i = 0; i < numRocksSameColour; i++)
    {
        dist[i] = INT_MAX;
        predecessor[i] = -1;
        vSet[i] = false;
        numRocksClimbed[i] = INT_MAX;
    }

    // Start from any rock at most reach units above the ground
    for (int i = 0; i < numRocksSameColour; i++)
    {
        if (rocksSameColour[i].row <= reach)
        {
            dist[i] = 0; // Distance to starting rocks is 0
            numRocksClimbed[i] = 0;
        }
    }

    while (!vSetIsEmpty(vSet, numRocksSameColour))
    {
        int vertex = findMinVertex(vSet, dist, numRocksSameColour);
        if (vertex == -1)
        {
            break; // No more reachable vertices
        }
        struct rock v = rocksSameColour[vertex];

        for (int i = 0; i < numRocksSameColour; i++)
        {
            struct rock w = rocksSameColour[i];

            if (straightDist(v.row, v.col, w.row, w.col) <= reach && !vSet[i])
            {
                double distance = straightDist(v.row, v.col, w.row, w.col);
                if (distance <= reach && !vSet[i])
                {
                    int rocksClimbed = numRocksClimbed[vertex] +
                                       1; // Climbing to w requires climbing one more rock
                    if (rocksClimbed < numRocksClimbed[i])
                    {
                        dist[i] = rocksClimbed; // Update the distance as the number of
                                                // rocks climbed
                        numRocksClimbed[i] = rocksClimbed;
                        predecessor[i] = vertex;
                    }
                }
            }
        }
        vSet[vertex] = true;
    }

    int numEndPoints = 0;
    int *endPoints = calloc(numRocksSameColour, sizeof(int));
    for (int i = 0; i < numRocksSameColour; i++)
    {
        if (WallHeight(w) - rocksSameColour[i].row <= reach)
        {
            endPoints[numEndPoints++] = i;
        }
    }

    // Find the minimum number of rocks climbed among end points
    int minRocksClimbed = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < numEndPoints; i++)
    {
        if (numRocksClimbed[endPoints[i]] < minRocksClimbed)
        {
            minRocksClimbed = numRocksClimbed[endPoints[i]];
            minIndex = endPoints[i];
        }
    }

    // Trace back the path from the minimum endpoint to the starting point
    Stack s = StackNew();
    int current = minIndex;
    while (current != -1)
    {
        StackPush(s, rocksSameColour[current]);
        current = predecessor[current];
    }

    // Allocate memory for path rocks
    int i = 0;
    while (!StackIsEmpty(s))
    {
        p.rocks[i++] = StackPop(s);
        p.numRocks++;
    }

    StackFree(s);

    free(rocksSameColour);
    free(endPoints);
    free(dist);
    free(predecessor);
    free(vSet);
    free(numRocksClimbed);
    return p;
}

static bool vSetIsEmpty(bool *vSet, int numRocks)
{
    for (int i = 0; i < numRocks; i++)
    {
        if (!vSet[i])
        {
            return false;
        }
    }
    return true;
}

static int findMinVertex(bool *vSet, int *dist, int numRocks)
{
    int min = INT_MAX;
    int index = -1;
    for (int i = 0; i < numRocks; i++)
    {
        if (dist[i] < min && !vSet[i])
        {
            min = dist[i];
            index = i;
        }
    }

    return index;
}

static double straightDist(int r1, int c1, int r2, int c2)
{
    return sqrt(pow((double)(r1 - r2), 2) + pow((double)(c1 - c2), 2));
}

struct path findMinEnergyPath(Wall w, int reach, int energyCosts[NUM_COLOURS])
{
    // TODO - Task 3
    // Allocate memory for rocks array
    struct rock *rocksArray = calloc(WallNumRocks(w), sizeof(struct rock));
    if (rocksArray == NULL)
    {
        return (struct path){0, NULL};
    }

    // Get all rocks from the wall
    int numRocks = WallGetAllRocks(w, rocksArray);

    // Count the number of starting points
    int numStartPoints = 0;
    for (int i = 0; i < numRocks; i++)
    {
        if (rocksArray[i].row <= reach)
        {
            numStartPoints++;
        }
    }

    // If there are no starting points, return an empty path
    if (numStartPoints == 0)
    {
        free(rocksArray);
        return (struct path){0, NULL};
    }

    // Find the minimum energy path
    struct path p = {0, NULL};
    p = findMinEnergyPathHelper(p, w, reach, energyCosts, rocksArray, numRocks);

    // Free allocated memory
    free(rocksArray);

    return p;
}

static struct path findMinEnergyPathHelper(struct path p, Wall wall, int reach,
                                    int *energyCosts, struct rock *rocks,
                                    int numRocks)
{
    // Allocate memory for distance, predecessor, visited set, and number of rocks
    // climbed arrays
    int *dist = calloc(numRocks, sizeof(int));
    int *predecessor = calloc(numRocks, sizeof(int));
    bool *vSet = calloc(numRocks, sizeof(bool));
    int *numRocksClimbed = calloc(numRocks, sizeof(int));

    // Check if memory allocation is successful
    if (!dist || !predecessor || !vSet || !numRocksClimbed)
    {
        free(dist);
        free(predecessor);
        free(vSet);
        free(numRocksClimbed);
        return (struct path){0, NULL};
    }

    // Initialize arrays
    for (int i = 0; i < numRocks; i++)
    {
        dist[i] = INT_MAX;
        predecessor[i] = -1;
        vSet[i] = false;
        numRocksClimbed[i] = INT_MAX;
    }

    // Start from any rock at most reach units above the ground
    for (int i = 0; i < numRocks; i++)
    {
        if (rocks[i].row <= reach)
        {
            dist[i] = 0; // Distance to starting rocks is 0
            numRocksClimbed[i] = 0;
        }
    }

    while (!vSetIsEmpty(vSet, numRocks))
    {
        int vertex = findMinVertex(vSet, dist, numRocks);
        if (vertex == -1)
        {
            break; // No more reachable vertices
        }
        struct rock v = rocks[vertex];

        for (int i = 0; i < numRocks; i++)
        {
            struct rock w = rocks[i];
            if (!vSet[i])
            {
                int energyCost = energyCosts[WallGetRockColour(wall, w.row, w.col)];
                double distance = straightDist(v.row, v.col, w.row, w.col);
                if (distance <= reach)
                {
                    int rocksClimbed =
                        numRocksClimbed[vertex] +
                        energyCost; // Climbing to w requires climbing one more rock
                    if (rocksClimbed < numRocksClimbed[i])
                    {
                        dist[i] = rocksClimbed; // Update the distance as the number of
                                                // rocks climbed
                        numRocksClimbed[i] = rocksClimbed;
                        predecessor[i] = vertex;
                    }
                }
            }
        }
        vSet[vertex] = true;
    }

    // Find the index of the endpoint with minimum energy
    int minEnergyIndex = -1;
    for (int i = 0; i < numRocks; i++)
    {
        if (WallHeight(wall) - rocks[i].row <= reach)
        {
            if (minEnergyIndex == -1 ||
                numRocksClimbed[i] < numRocksClimbed[minEnergyIndex])
            {
                minEnergyIndex = i;
            }
        }
    }

    // Trace back the path from the endpoint with minimum energy
    Stack s = StackNew();
    int current = minEnergyIndex;
    while (current != -1)
    {
        StackPush(s, rocks[current]);
        current = predecessor[current];
    }

    // Allocate memory for path rocks
    int pathLength = StackSize(s);
    p.numRocks = pathLength;
    p.rocks = calloc(pathLength, sizeof(struct rock));

    // Pop elements from stack and store them in the path array
    for (int i = 0; i < pathLength; i++)
    {
        p.rocks[i] = StackPop(s);
    }

    // Free allocated memory and return the path
    StackFree(s);
    free(dist);
    free(predecessor);
    free(vSet);
    free(numRocksClimbed);
    return p;
}

struct path findMinTurnsPath(Wall w, int reach, int energyCosts[NUM_COLOURS],
                             int maxEnergy)
{
    // TODO - Task 4
    // Allocate memory for rocks array
    struct rock *rocksArray = calloc(WallNumRocks(w), sizeof(struct rock));
    if (rocksArray == NULL)
    {
        return (struct path){0, NULL};
    }

    // Get all rocks from the wall
    int numRocks = WallGetAllRocks(w, rocksArray);

    // Count the number of starting points
    int numStartPoints = 0;
    for (int i = 0; i < numRocks; i++)
    {
        if (rocksArray[i].row <= reach)
        {
            numStartPoints++;
        }
    }

    // If there are no starting points, return an empty path
    if (numStartPoints == 0)
    {
        free(rocksArray);
        return (struct path){0, NULL};
    }

    struct path p = {0, NULL};
    return findMinTurnsPathHelper(p, w, reach, energyCosts, maxEnergy, rocksArray,
                                  numRocks);
}

static struct path findMinTurnsPathHelper(struct path p, Wall wall, int reach,
                                   int *energyCosts, int maxEnergy,
                                   struct rock *rocks, int numRocks)
{
    // Allocate memory for distance, predecessor, visited set, and number of rocks
    // climbed arrays
    int *dist = calloc(numRocks, sizeof(int));
    int *predecessor = calloc(numRocks, sizeof(int));
    bool *vSet = calloc(numRocks, sizeof(bool));
    int *numRocksClimbed = calloc(numRocks, sizeof(int));

    // Check if memory allocation is successful
    if (!dist || !predecessor || !vSet || !numRocksClimbed)
    {
        free(dist);
        free(predecessor);
        free(vSet);
        free(numRocksClimbed);
        return (struct path){0, NULL};
    }

    // Initialize arrays
    for (int i = 0; i < numRocks; i++)
    {
        dist[i] = INT_MAX;
        predecessor[i] = -1;
        vSet[i] = false;
        numRocksClimbed[i] = INT_MAX;
    }

    // Start from any rock at most reach units above the ground
    for (int i = 0; i < numRocks; i++)
    {
        if (rocks[i].row <= reach)
        {
            dist[i] = 0; // Distance to starting rocks is 0
            numRocksClimbed[i] = 0;
        }
    }

    while (!vSetIsEmpty(vSet, numRocks))
    {
        int vertex = findMinVertex(vSet, dist, numRocks);
        if (vertex == -1)
        {
            break; // No more reachable vertices
        }
        struct rock v = rocks[vertex];

        for (int i = 0; i < numRocks; i++)
        {
            struct rock w = rocks[i];
            if (!vSet[i])
            {
                int energy = energyCosts[WallGetRockColour(wall, w.row, w.col)];
                double distance = straightDist(v.row, v.col, w.row, w.col);
                if (distance <= reach)
                {
                    int rocksClimbed =
                        numRocksClimbed[vertex] +
                        energy; // Climbing to w requires climbing one more rock
                    if (rocksClimbed < numRocksClimbed[i])
                    {
                        dist[i] = rocksClimbed; // Update the distance as the number of
                                                // rocks climbed
                        numRocksClimbed[i] = rocksClimbed;
                        predecessor[i] = vertex;
                    }
                }
            }
        }
        vSet[vertex] = true;
    }

    // Find the index of the endpoint with minimum energy
    int minEnergyIndex = -1;
    for (int i = 0; i < numRocks; i++)
    {
        if (WallHeight(wall) - rocks[i].row <= reach)
        {
            if (minEnergyIndex == -1 ||
                numRocksClimbed[i] < numRocksClimbed[minEnergyIndex])
            {
                minEnergyIndex = i;
            }
        }
    }

    // Trace back the path from the endpoint with minimum energy
    Stack s = StackNew();
    int current = minEnergyIndex;
    while (current != -1)
    {
        StackPush(s, rocks[current]);
        current = predecessor[current];
    }

    // Allocate memory for path rocks
    int stackSize = StackSize(s);
    p.numRocks = 0;
    p.rocks = calloc(ARRAY_SIZE, sizeof(struct rock));

    // Pop elements from stack and store them in the path array
    int energy = maxEnergy;
    for (int i = 0; i < stackSize; i++)
    {
        struct rock rockToClimb = StackPop(s);
        p.rocks[p.numRocks++] = rockToClimb;
        energy -= energyCosts[rockToClimb.colour];

        // Check if there's enough energy to climb the next rock
        if (i < stackSize - 1)
        {
            struct rock nextRockToClimb = StackTop(s);
            if (energy < energyCosts[nextRockToClimb.colour])
            {
                // Rest on the current rock
                p.rocks[p.numRocks++] = rockToClimb;
                energy = maxEnergy; // Energy is refilled
            }
        }
    }

    // Free allocated memory and return the path
    StackFree(s);
    free(dist);
    free(predecessor);
    free(vSet);
    free(numRocksClimbed);
    free(rocks);
    return p;
}