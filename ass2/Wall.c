// Implementation of the Wall ADT

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Wall.h"

struct wall {
    // TODO
    int height;
    int width;
    int numRocks;

    int **matrix;
};

static int compareRocks(const void *ptr1, const void *ptr2);

static void freeState(Wall w);
static bool validCell(Wall m, struct rock rock);
static double straightDist(int r1, int c1, int r2, int c2);
/**
 * Creates a new blank wall with the given dimensions
 */
Wall WallNew(int height, int width) {
    // TODO
    Wall w = malloc(sizeof(struct wall));
    if (!w) {
        return NULL;
    }
    w->height = height;
    w->width = width;
    w->numRocks = 0;
    w->matrix = malloc(height * sizeof(int *));
    
    if (!w->matrix) {
        free(w);
        return NULL;
    }
    
    for (int i = 0; i < w->height; i++) {
        w->matrix[i] = calloc(width, sizeof(int));
        if (!w->matrix[i]) {
            freeState(w);
            return NULL;
        }

        for (int j = 0; j < w->width; j++) {
            w->matrix[i][j] = NONE;
        }
    }
    return w;
}

/**
 * Frees all memory allocated to the wall 
 */
void WallFree(Wall w) {
    // TODO
    freeState(w);
    free(w);
}

static void freeState(Wall w) {
    for (int i = 0; i < w->height; i++) {
        free(w->matrix[i]);
    }
    free(w->matrix);
}

/**
 * Returns the height of the wall
 */
int WallHeight(Wall w) {
    // TODO
    return w->height;
}

/**
 * Returns the width of the wall
 */
int WallWidth(Wall w) {
    // TODO
    return w->width;
}

/**
 * Adds a rock to the wall
 * If there is already a rock at the given coordinates, replaces it
 */
void WallAddRock(Wall w, struct rock rock) {
    assert(validCell(w, rock));
    w->matrix[rock.row][rock.col] = rock.colour; // Add the new rock
    w->numRocks++; // Increment numRocks
}

static bool validCell(Wall m, struct rock rock) {
    return (
        rock.row >= 0 && rock.row < m->height && rock.col >= 0 && rock.col < m->width
    );
}
/**
 * Returns the number of rocks on the wall
 */
int WallNumRocks(Wall w) {
    // TODO
    return w->numRocks;
}

/**
 * Returns the colour of the rock at the given coordinates, or NONE if
 * there is no rock at those coordinates.
 */
Colour WallGetRockColour(Wall w, int row, int col) {
    // TODO
    if (w->matrix[row][col] == 0) {
        return GREEN;
    } else if (w->matrix[row][col] == 1) {
        return TEAL;
    } else if (w->matrix[row][col] == 2) {
        return PINK;
    } else if (w->matrix[row][col] == 3) {
        return RED;
    } else {
        return NONE;
    }
}

/**
 * Stores all rocks on the wall in the given `rocks` array and returns
 * the number of rocks stored. Assumes that the array is at least as
 * large as the number of rocks on the wall.
 */
int WallGetAllRocks(Wall w, struct rock rocks[]) {
    // TODO
    int stored = 0;
    for (int i = 0; i < w->height; i++) {
        for (int j = 0; j < w->width; j++) {
            if (w->matrix[i][j] != -1) {
                rocks[stored].row = i;
                rocks[stored].col = j;
                rocks[stored].colour = w->matrix[i][j]; 
                stored++;
            }
        }
    }
    return stored;
}

/**
 * Stores all rocks that are within a distance of `dist` from the given
 * coordinates in the given `rocks` array and returns the number of rocks
 * stored. Assumes that the array is at least as large as the number of
 * rocks on the wall.
 */
int WallGetRocksInRange(Wall w, int row, int col, int dist,
                        struct rock rocks[]) {
    // TODO
    int stored = 0;
    for (int i = 0; i < w->height; i++) {
        for (int j = 0; j < w->width; j++) {
            if (w->matrix[i][j] != -1 && straightDist(i, j, row, col) <= dist) {
                rocks[stored].row = i;
                rocks[stored].col = j;
                rocks[stored].colour = w->matrix[i][j];
                stored++;
            }
        }
    }
    return stored;
}

static double straightDist(int r1, int c1, int r2, int c2) {
    return sqrt(pow((double)(r1 - r2), 2) + pow((double)(c1 - c2), 2));
}


/**
 * Stores all rocks with the colour `colour` that are within a distance
 * of `dist` from the given coordinates in the given `rocks` array and
 * returns the number of rocks stored. Assumes that the array is at
 * least as large as the number of rocks on the wall.
 */
int WallGetColouredRocksInRange(Wall w, int row, int col, int dist,
                                Colour colour, struct rock rocks[]) {
    // TODO
    int stored = 0;
    for (int i = 0; i < w->height; i++) {
        for (int j = 0; j < w->width; j++) {
            if (w->matrix[i][j] == colour && straightDist(i, j, row, col) <= dist) {
                rocks[stored].row = i;
                rocks[stored].col = j;
                rocks[stored].colour = w->matrix[i][j];
                stored++;
            }
        }
    }
    return stored;
}

////////////////////////////////////////////////////////////////////////

/**
 * Prints the wall out in a nice format
 * NOTE: DO NOT MODIFY THIS FUNCTION! This function will work once
 *       WallGetAllRocks and all the functions above it work.
 */
void WallPrint(Wall w) {
    int height = WallHeight(w);
    int width = WallWidth(w);
    int numRocks = WallNumRocks(w);
    struct rock *rocks = malloc(numRocks * sizeof(struct rock));
    WallGetAllRocks(w, rocks);
    qsort(rocks, numRocks, sizeof(struct rock), compareRocks);

    int i = 0;
    for (int y = height; y >= 0; y--) {
        for (int x = 0; x <= width; x++) {
            if ((y == 0 || y == height) && (x == 0 || x % 5 == 0)) {
                printf("+ ");
            } else if ((x == 0 || x == width) && (y == 0 || y % 5 == 0)) {
                printf("+ ");
            } else if (y == 0 || y == height) {
                printf("- ");
            } else if (x == 0 || x == width) {
                printf("| ");
            } else if (i < numRocks && y == rocks[i].row && x == rocks[i].col) {
                char *color;
                switch (rocks[i].colour) {
                    case GREEN: color = "\x1B[32m"; break;
                    case TEAL:  color = "\x1B[96m"; break;
                    case PINK:  color = "\x1B[95m"; break;
                    case RED:   color = "\x1B[91m"; break;
                    default:    color = "\x1B[0m";  break;
                }
                printf("%so %s", color, RESET);
                i++;
            } else {
                printf("\u00B7 ");
            }
        }
        printf("\n");
    }

    free(rocks);
}

static int compareRocks(const void *ptr1, const void *ptr2) {
    struct rock *r1 = (struct rock *)ptr1;
    struct rock *r2 = (struct rock *)ptr2;
    if (r1->row != r2->row) {
        return r2->row - r1->row;
    } else {
        return r1->col - r2->col;
    }
}

