
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree newNode(int value) {
	BSTree new = malloc(sizeof(*new));
	if (!new) {
		return NULL;
	}
	new->value = value;
	new->left = new->right = NULL;
	return new;
}
BSTree BSTreeInsert(BSTree t, int val) {
	// TODO
	if (!t) {
		return newNode(val);
	}
	if (t->value == val) {
		return t;
	}
	if (val < t->value) {
		t->left = BSTreeInsert(t->left, val);
	} 
	if (val > t->value) {
		t->right = BSTreeInsert(t->right, val);
	}
	return t;
}

