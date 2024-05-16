
#include "list.h"


bool search(Node current, int value) {
	if (!current) {
		return false;
	}
	if (current->value == value) {
		return true;
	}
	return search(current->next, value);
}

Node listAppend(Node current, int value) {
	if (!current) {
		return newNode(value);
	}
	current->next = listAppend(current->next, value);
	return current;
}	

Node listSetIntersectionHelper(List s3, Node s1, List s2) {
	if (!s1) {
		return NULL;
	}
	if (search(s2->head, s1->value)) {
		s3->head = listAppend(s3->head, s1->value);
	}
	
	listSetIntersectionHelper(s3, s1->next, s2);
	return s3->head;
}
List listSetIntersection(List s1, List s2) {
	// TODO
	List s3 = newList();
	if (!s1 || !s2) {
		return NULL;
	}
	s3->head = listSetIntersectionHelper(s3, s1->head, s2);
	return s3;
}

