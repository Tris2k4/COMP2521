
#include "tree.h"

Tree newNode(int value) {
	Tree new = malloc(sizeof(*new));
	if (!new) {
		return NULL;
	}
	new->value = value;
	new->left = new->right = NULL;
	return new;
}

struct node *bstInsert(struct node *tree, int val) {
	if (tree == NULL) {
		return newNode(val);
	} else if (val < tree->value) {
		tree->left = bstInsert(tree->left, val);
	} else if (val > tree->value) {
		tree->right = bstInsert(tree->right, val);
	}
	return tree;
}

Tree TreeCopyHelper(Tree t, int depth, int currentDepth, Tree new) {
	if (!t || currentDepth > depth) {
		return NULL;
	}
	new = bstInsert(new, t->value);
	TreeCopyHelper(t->left, depth, currentDepth + 1, new);
	TreeCopyHelper(t->right, depth, currentDepth + 1, new);
	return new;
}
Tree TreeCopy(Tree t, int depth) {
	// TODO
	if (depth < 0) {
		return NULL;
	}
	Tree new = NULL;
	return TreeCopyHelper(t, depth, 0, new);
}

