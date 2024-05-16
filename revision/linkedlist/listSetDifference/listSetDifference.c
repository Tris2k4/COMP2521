
#include "list.h"

bool search(Node list2, int value) {
	if (!list2) {
		return false;
	}
	if (list2->value == value) {
		return true;
	}
	return search(list2->next, value);
}

Node listAppend(Node s3, int value) {
	if (!s3) {
		return newNode(value);
	}
	s3->next = listAppend(s3->next, value);
	return s3;
}

Node listSetDifferenceHelper(List s3, Node list1, List l2) {
	if (!list1) {
		return NULL;
	}
	if (!search(l2->head, list1->value)) {
		s3->head = listAppend(s3->head, list1->value); 
	}
	listSetDifferenceHelper(s3, list1->next, l2);
	return s3->head;
}

List listSetDifference(List l1, List l2) {
	// TODO
	if (!l1) {
		return NULL;
	}
	if (!l2) {
		return l1;
	}
	List s3 = newList();
	s3->head = listSetDifferenceHelper(s3, l1->head, l2);
	return s3;
}

