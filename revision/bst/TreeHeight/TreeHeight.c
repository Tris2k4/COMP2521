
#include <stdlib.h>

#include "tree.h"

int max(int a, int b) {
    return (a > b ? a : b);
}
int TreeHeight(Tree t) {
    if (!t) {
        return -1;
    }
    int left = 1 + TreeHeight(t->left);
    int right = 1 + TreeHeight(t->right);

    return max(left, right);
}

