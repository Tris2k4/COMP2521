
#include "list.h"

Node set3Insert(Node set3, int value) {
	if (!set3) {
		return newNode(value);
	} else if (set3->value == value) {
		return set3;
	} else {
		set3->next = set3Insert(set3->next, value); 
	}

	return set3;
}

Node listSetInsert(Node current, List set3) {
	if (!current) {
		return NULL;
	}

	listSetInsert(current->next, set3);
	set3->head = set3Insert(set3->head, current->value);
	return set3->head;
}



Node listSetInsert2(Node current, List set3) {
    if (!current) {
        return NULL;
    }
    set3->head = set3Insert(set3->head, current->value); // Insert element into set3
    return listSetInsert2(current->next, set3);
}


List listSetUnion(List s1, List s2) {
	// TODO
	List s3 = newList();
	listSetInsert(s1->head, s3);
	listSetInsert2(s2->head, s3);

	
	return s3;
}

