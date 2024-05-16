
#include "list.h"

bool listIsOrderedAscending(Node l) {
	if (!l || !l->next) {
		return true;
	}
	if (l->value > l->next->value) {
		return false;
	}
	return listIsOrderedAscending(l->next);
}

bool listIsOrderedDescending(Node l) {
	if (!l || !l->next) {
		return true;
	}
	if (l->value < l->next->value) {
		return false;
	}
	return listIsOrderedDescending(l->next);
}

bool isAscending(Node l) {
    if (!l || !l->next) {
        return true;
    }
    return (l->value < l->next->value);
}

bool listIsOrdered(List l) {
	// TODO
	if (!l) {
		return true;
	}
	return (isAscending(l->head) ? listIsOrderedAscending(l->head) : listIsOrderedDescending(l->head));	
}

