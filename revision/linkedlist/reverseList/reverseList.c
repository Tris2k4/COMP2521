
#include "list.h"

Node listReverseHelper(Node current) {
	if (!current || !current->next) {
		return current;
	}
	Node reversedHead = listReverseHelper(current->next);
	Node front = current->next;
	front->next = current;
	current->next = NULL;
	return reversedHead;
}

void listReverse(List l) {
	// TODO
	if (!l) {
		return;
	}
	l->head = listReverseHelper(l->head);
}

