
#include <stdlib.h>

#include "BSTree.h"

bool BSTreeNodeDepthHelper(BSTree t, int key, int *depth) {
	if (!t) {
		return false;
	}
	if (key < t->value) {
		*depth += 1;
		return BSTreeNodeDepthHelper(t->left, key, depth);
	}
	if (key > t->value) {
		*depth += 1;
		return BSTreeNodeDepthHelper(t->right, key, depth);
	}
	if (key == t->value) {
		return true;
	}
	return false;
}
int BSTreeNodeDepth(BSTree t, int key) {
	int depth = 0;
	return (BSTreeNodeDepthHelper(t, key, &depth) ? depth : -1);
}

