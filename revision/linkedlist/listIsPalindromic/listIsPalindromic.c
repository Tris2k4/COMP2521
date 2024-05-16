
#include "list.h"

bool listIsPalindromicHelper(Node first, Node last, int left, int right) {
	if (first->value != last->value) {
		return false;
	}
	if (!first->next && !last->prev) {
		return true; 
	}
	return listIsPalindromicHelper(first->next, last->prev, left++, right--);
}

bool listIsPalindromic(List l) {
	// TODO
	int left = 0;
	int right = l->size;
	Node first = l->first;
	Node last = l->last;

	if (l->size <= 1) {
		return true;
	}
	return listIsPalindromicHelper(first, last, left, right);
}

