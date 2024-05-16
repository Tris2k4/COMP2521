
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

void TreeCountNodes(Tree t, int *count) {
	if (!t) {
		return;
	}
	*count += 1;
	TreeCountNodes(t->left, count);
	TreeCountNodes(t->right, count);
}

bool TreeIsPerfectlyBalanced(Tree t) {
    if (!t) {
        return true; // An empty tree is perfectly balanced
    }

    int leftCount = 0;
    int rightCount = 0;
    TreeCountNodes(t->left, &leftCount);
    TreeCountNodes(t->right, &rightCount);

    if (abs(leftCount - rightCount) > 1) {
        return false;
    }
    return TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right);
}

