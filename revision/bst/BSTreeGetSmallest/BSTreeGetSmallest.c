
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	// TODO
	if (!t) {
		return NULL;
	}
	if (!t->left) {
		return t;
	}

	return BSTreeGetSmallest(t->left);
}

