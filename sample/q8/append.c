
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// WARNING: while loops, for loops, do loops and goto statements are
//          strictly forbidden.

struct node *appendHelper(struct node *list1, struct node *list2) {
    if (!list1->next) {
        list1->next = list2;
        return list1;
    }
    list1->next = appendHelper(list1->next, list2);
    return list1;
}
struct node *append(struct node *l1, struct node *l2) {
    // TODO
    if (!l1 && !l2) {
        return NULL;
    }
    if (!l1) {
        return l2;
    }
    if (!l2) {
        return l1;
    }
    return appendHelper(l1, l2);
}

