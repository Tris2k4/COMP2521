
#include "list.h"

void findMax(Node current, int *max) {
	if (!current) {
		return;
	}

	if (current->value > *max) {
		*max = current->value;
	}

	return findMax(current->next, max);
}

Node listDeleteLargestHelper(Node head, Node previous, Node current, int max) {
	if (!current) {
		return NULL;
	}
	if (head->value == max) {
		Node temp = head;
		head = head->next;
		free(temp);
		return head;
	}
	if (current->value == max) {
		Node temp = current;
		previous->next = current->next;
		current = current->next;
		free(temp);
		return current;
	}
	listDeleteLargestHelper(head, current, current->next, max);
	return head;
}

int listDeleteLargest(List l) {
	int max = -1e9;
	findMax(l->head, &max);

	l->head = listDeleteLargestHelper(l->head, NULL, l->head, max);
	return max;
}

