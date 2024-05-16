
#include <stdlib.h>

#include "BSTree.h"


void BSTTreeGetKthHelper(BSTree t, int k, int *track, int *res) {
	if (!t) {
		return;
	}
	BSTTreeGetKthHelper(t->left, k, track, res);
	*track += 1;
	if (*track - 1 == k) {
		*res = t->value;
		return;
	}
	BSTTreeGetKthHelper(t->right, k, track, res);
}

int BSTreeGetKth(BSTree t, int k) {
	// TODO
	int track = 0, ans = 0;
	BSTTreeGetKthHelper(t, k, &track, &ans);
	return ans;
}

