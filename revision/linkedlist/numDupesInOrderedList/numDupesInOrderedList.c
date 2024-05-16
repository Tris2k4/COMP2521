
#include "list.h"

int numDupesInOrderedListHelper(Node current, int *count) {
	if (!current->next) {
		return *count;
	}
	if (current->value == current->next->value) {
		*count += 1;
	}
	return numDupesInOrderedListHelper(current->next, count);
}

int numDupesInOrderedList(List l) {
	// TODO
	int count = 0;
	return numDupesInOrderedListHelper(l->head, &count);
}

