// COMP2521 - Assignment 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Set.h"
#include "SetStructs.h"

void testSetInsert(void);


void testSetDelete(void);
void testSetDeleteGeneral(void);
void testSetDelete2(void);
void testSetDelete3(void);

void testSetSize(void);



void testSetContains(void);



void testSetPrint(void);
void testSetPrintGeneral(void);
void testSetPrintEmpty(void);


void checkFileContents(FILE *file, char *str);


void testSetUnion(void);
void testSetUnionTest1(void);
void testSetUnionTest2(void);
void testSetUnionTest3(void);

void testSetIntersection(void);
void testSetIntersectionGeneral(void);
void testSetIntersectionTest1(void);
void testSetIntersectionTest2(void);


void testSetEquals(void);
void testSetEqualsGeneral(void);
void testSetEqualsSizeNotEqual(void);
void testSetEqualsNotEqual(void);
void testSetEqualsEmpty(void);


void testSetSubset(void);
void testSetSubsetGeneral(void);
void testSetSubsetTest2(void);
void testSetSubsetTest3(void);
void testBalance1(void);


void testBalance2(void);
void testBalance2General(void);
void testBalance2Test2(void);
void testBalance2Test3(void);

bool isHeightBalanced(struct node *t);


bool doIsHeightBalanced(struct node *t, int *height);

void testSetAtIndex(void);
void testSetAtIndexGeneral(void);
void testSetAtIndexTest1(void);
void testSetAtIndexTest2(void);
void testSetAtIndexTest3(void);
void testSetAtIndexTest4(void);
void testSetAtIndexTest5(void);
void testSetAtIndexTest6(void);

void testSetIndexOf(void);
void testSetIndexOfGeneral(void);
void testSetIndexOfTest1(void);
void testSetIndexOfTest2(void);
void testSetIndexOfTest3(void);
void testSetIndexOfTest4(void);

void testSetCursor1(void);
void testSetCursor2(void);

void doBstPrint(struct node *t, FILE *out);





int main(int argc, char *argv[]) {
	testSetInsert();
	testSetDelete();
	testSetSize();
	testSetContains();
	testSetPrint();

	testSetUnion();
	testSetIntersection();
	testSetEquals();
	testSetSubset();

	testBalance1();
	testBalance2();

	testSetAtIndex();
	testSetIndexOf();

	// testSetCursor1();
	// testSetCursor2();
}

void testSetInsert(void) {
	// NOTE: SetInsert can't be tested on its own unless we directly
	//       access the internal representation of the ADT

	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetSize(s) == 4);
	SetInsert(s, 5);
	assert(SetSize(s) == 4);

	SetFree(s);
}

void testSetDelete(void) {
	// NOTE: SetDelete can't be tested without SetInsert

	testSetDeleteGeneral();
	testSetDelete2();
	testSetDelete3();
}

void testSetDeleteGeneral(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	SetDelete(s, 2);
	assert(SetSize(s) == 3);
	SetDelete(s, 8);
	assert(SetSize(s) == 2);
	SetDelete(s, 3);
	assert(SetSize(s) == 2);

	SetFree(s);
}
void testSetDelete2(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 1);
	SetInsert(s, 4);
	SetInsert(s, 7);
	SetInsert(s, 8);
	// doBstPrint(s->tree, stdout);

	printf("\n");

	SetDelete(s, 5);
	// doBstPrint(s->tree, stdout);
	assert(SetSize(s) == 5);

	printf("\n");

	SetInsert(s, 5);
	assert(SetSize(s) == 6);
	// doBstPrint(s->tree, stdout);

	printf("\n");

	SetDelete(s, 4);
	// doBstPrint(s->tree, stdout);
	assert(SetSize(s) == 5);
	SetFree(s);
}

void testSetDelete3(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 1);
	SetInsert(s, 4);
	SetInsert(s, 7);
	SetInsert(s, 8);
	
	SetDelete(s, 5);
	SetDelete(s, 2);
	SetDelete(s, 1);
	SetDelete(s, 4);
	SetDelete(s, 7);
	SetDelete(s, 8);
	// doBstPrint(s->tree, stdout);

	assert(SetSize(s) == 0);

	
	SetFree(s);
}

void testSetSize(void) {
	Set s = SetNew();
	assert(SetSize(s) == 0);
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetSize(s) == 4);
	SetInsert(s, 7);
	SetInsert(s, 2);
	assert(SetSize(s) == 5);

	SetFree(s);
}

void testSetContains(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	assert(SetContains(s, 2));
	assert(SetContains(s, 4));
	assert(SetContains(s, 5));
	assert(SetContains(s, 8));
	assert(!SetContains(s, 3));

	SetFree(s);
}

void testSetPrint(void) {
	testSetPrintGeneral();
	testSetPrintEmpty();
}

void testSetPrintGeneral(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	FILE *out = tmpfile();
	SetPrint(s, out);
	rewind(out);
    int c;
    while ((c = fgetc(out)) != EOF) {
        putchar(c);
    }
    putchar('\n');
	checkFileContents(out, "{2, 4, 5, 8}");
	fclose(out);

	SetFree(s);
}

void testSetPrintEmpty(void) {
	Set s = SetNew();
	FILE *out = tmpfile();
	SetPrint(s, out);
	rewind(out);
    int c;
    while ((c = fgetc(out)) != EOF) {
        putchar(c);
    }
    putchar('\n');
	checkFileContents(out, "{}");
	fclose(out);
	SetFree(s);
}

/**
 * This function checks if the contents of a file matches the expected
 * contents. If the contents do not match, the program will exit with an
 * assertion error.
 */
void checkFileContents(FILE *file, char *expectedContents) {
	fflush(file);
	fseek(file, 0, SEEK_SET);
	char *line = NULL;
	size_t n = 0;
	getline(&line, &n, file);
	assert(strcmp(line, expectedContents) == 0);
	free(line);
}

////////////////////////////////////////////////////////////////////////

void testSetUnion(void) {
	testSetUnionTest1();
	testSetUnionTest2();
	testSetUnionTest3();
}
void testSetUnionTest1(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	doBstPrint(a->tree, stdout);
	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);
	doBstPrint(b->tree, stdout);

	Set c = SetUnion(a, b);
	assert(SetContains(c, 2));
	assert(SetContains(c, 3));
	assert(SetContains(c, 4));
	assert(SetContains(c, 5));
	assert(SetContains(c, 7));
	assert(SetContains(c, 8));
	assert(SetSize(c) == 6);
	doBstPrint(c->tree, stdout);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}
void testSetUnionTest2(void) {
	Set a = SetNew();
	
	// doBstPrint(a->tree, stdout);
	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);
	doBstPrint(b->tree, stdout);

	Set c = SetUnion(a, b);
	assert(SetContains(c, 3));
	assert(SetContains(c, 5));
	assert(SetContains(c, 7));
	assert(SetContains(c, 8));
	assert(SetSize(c) == 4);
	doBstPrint(c->tree, stdout);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}
void testSetUnionTest3(void) {
	Set a = SetNew();
	SetInsert(a, 3);
	SetInsert(a, 8);
	SetInsert(a, 7);
	SetInsert(a, 5);
	// doBstPrint(a->tree, stdout);
	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);
	doBstPrint(b->tree, stdout);

	Set c = SetUnion(a, b);
	assert(SetContains(c, 3));
	assert(SetContains(c, 5));
	assert(SetContains(c, 7));
	assert(SetContains(c, 8));
	assert(SetSize(c) == 4);
	doBstPrint(c->tree, stdout);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetIntersection(void) {
	testSetIntersectionGeneral();
	testSetIntersectionTest1();
	testSetIntersectionTest2();
}
void testSetIntersectionGeneral(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetIntersection(a, b);
	doBstPrint(c->tree, stdout);
	assert(SetContains(c, 5));
	assert(SetContains(c, 8));
	assert(!SetContains(c, 2));
	assert(!SetContains(c, 3));
	assert(!SetContains(c, 4));
	assert(!SetContains(c, 7));
	assert(SetSize(c) == 2);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetIntersectionTest1(void) {
	Set a = SetNew();

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetIntersection(a, b);
	doBstPrint(c->tree, stdout);
	assert(!SetContains(c, 5));
	assert(!SetContains(c, 8));
	assert(!SetContains(c, 3));
	assert(!SetContains(c, 7));
	assert(SetSize(c) == 0);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}
void testSetIntersectionTest2(void) {
	Set a = SetNew();

	Set b = SetNew();


	Set c = SetIntersection(a, b);
	doBstPrint(c->tree, stdout);
	assert(SetSize(c) == 0);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetEquals(void) {
	testSetEqualsGeneral();
	testSetEqualsSizeNotEqual();
	testSetEqualsNotEqual();
	testSetEqualsEmpty();

}

void testSetEqualsGeneral(void) {
	Set a = SetNew();
	SetInsert(a, 4);
	SetInsert(a, 2);
	SetInsert(a, 7);
	SetInsert(a, 1);

	Set b = SetNew();
	SetInsert(b, 2);
	SetInsert(b, 4);
	SetInsert(b, 1);
	SetInsert(b, 7);

	Set c = SetNew();
	SetInsert(c, 4);
	SetInsert(c, 2);
	SetInsert(c, 7);
	SetInsert(c, 3);

	assert(SetEquals(a, b));
	assert(!SetEquals(a, c));

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetEqualsSizeNotEqual(void) {
	Set a = SetNew();
	SetInsert(a, 4);
	SetInsert(a, 2);
	SetInsert(a, 7);
	SetInsert(a, 1);

	Set b = SetNew();
	SetInsert(b, 2);
	SetInsert(b, 4);
	SetInsert(b, 1);

	assert(!SetEquals(a, b));
	SetFree(a);
	SetFree(b);
}

void testSetEqualsNotEqual(void) {
	Set a = SetNew();
	SetInsert(a, 4);
	SetInsert(a, 2);
	SetInsert(a, 7);
	SetInsert(a, 1);
	SetInsert(a, 5);
	SetInsert(a, 9);
	SetInsert(a, 10);
	// doBstPrint(a->tree, stdout);

	printf("\n");


	Set c = SetNew();
	SetInsert(c, 4);
	SetInsert(c, 2);
	SetInsert(c, 7);
	SetInsert(c, 1);
	SetInsert(c, 6);
	SetInsert(c, 5);
	SetInsert(c, 10);
	doBstPrint(c->tree, stdout);
	assert(!SetEquals(a, c));
	SetFree(a);
	SetFree(c);
}

void testSetEqualsEmpty(void) {
	Set a = SetNew();
	Set c = SetNew();
	assert(SetEquals(a, c));
	SetFree(a);
	SetFree(c);
}




void testSetSubset(void) {
	testSetSubsetGeneral();
	testSetSubsetTest2();
	testSetSubsetTest3();

}


void testSetSubsetGeneral(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 3);
	SetInsert(a, 6);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 9);
	SetInsert(b, 5);
	SetInsert(b, 6);

	Set c = SetNew();
	SetInsert(c, 4);
	SetInsert(c, 6);
	SetInsert(c, 3);
	SetInsert(c, 7);

	assert(SetSubset(a, b));
	assert(!SetSubset(a, c));

	SetFree(a);
	SetFree(b);
	SetFree(c);
}


void testSetSubsetTest2(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 1);
	SetInsert(a, 4);
	SetInsert(a, 7);
	SetInsert(a, 8);
	SetInsert(a, 9);

	Set b = SetNew();
	SetInsert(b, 5);
	SetInsert(b, 9);
	SetInsert(b, 1);
	SetInsert(b, 2);

	Set c = SetNew();
	SetInsert(c, 5);
	SetInsert(c, 2);
	SetInsert(c, 1);
	SetInsert(c, 10);
	SetInsert(c, 7);
	SetInsert(c, 8);
	SetInsert(c, 9);

	assert(SetSubset(a, b));
	assert(!SetSubset(a, c));

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetSubsetTest3(void) {
	Set a = SetNew();

	Set b = SetNew();
	SetInsert(b, 5);
	SetInsert(b, 9);
	SetInsert(b, 1);
	SetInsert(b, 2);



	assert(SetSubset(a, b));


	SetFree(a);
	SetFree(b);
}
////////////////////////////////////////////////////////////////////////

void testBalance1(void) {
	Set s = SetNew();

	SetInsert(s, 8);
	SetInsert(s, 5);
	SetInsert(s, 2);
	doBstPrint(s->tree, stdout);
	// The tree should have been rebalanced after inserting 2
	// NOTE: Normally, a user should not have access to the concrete
	//       representation of an ADT, but since we have #included
	//       SetStructs.h, we have access for testing purposes.
	assert(isHeightBalanced(s->tree));

	SetFree(s);
}

void testBalance2(void) {
	testBalance2General();
	testBalance2Test2();
	testBalance2Test3();
}

void testBalance2General(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetDelete(s, 7);

	doBstPrint(s->tree, stdout);
	// The tree should have been rebalanced after deleting 7
	assert(isHeightBalanced(s->tree));

	SetFree(s);
}

void testBalance2Test2(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 10);
	SetInsert(s, 1);
	SetInsert(s, 8);
	SetInsert(s, 15);
	

	doBstPrint(s->tree, stdout);
	SetDelete(s, 6);
	SetDelete(s, 8);
	assert(SetSize(s) == 8);
	printf("\n");
	doBstPrint(s->tree, stdout);
	assert(isHeightBalanced(s->tree));

	SetFree(s);
}
void testBalance2Test3(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 1);
	SetInsert(s, 8);
	SetInsert(s, 15);
	

	doBstPrint(s->tree, stdout);

	printf("\n");

	SetDelete(s, 4);
	doBstPrint(s->tree, stdout);
	assert(SetSize(s) == 9);

	printf("\n");
	SetDelete(s, 6);
	assert(SetSize(s) == 8);
	printf("\n");
	doBstPrint(s->tree, stdout);
	assert(isHeightBalanced(s->tree));

	printf("\n");
	SetInsert(s, 10);
	doBstPrint(s->tree, stdout);


	printf("\n");

	SetDelete(s, 8);
	doBstPrint(s->tree, stdout);
	assert(SetSize(s) == 8);
	SetFree(s);
}

/**
 * Checks if the given tree is height-balanced
 */
bool isHeightBalanced(struct node *t) {
	int height = -1;
	return doIsHeightBalanced(t, &height);
}

bool doIsHeightBalanced(struct node *t, int *height) {
	if (t == NULL) {
		*height = -1;
		return true;
	}

	int lHeight = -1;
	int rHeight = -1;
	if (doIsHeightBalanced(t->left, &lHeight)
			&& doIsHeightBalanced(t->right, &rHeight)
			&& abs(lHeight - rHeight) <= 1) {
		*height = (lHeight > rHeight ? lHeight : rHeight) + 1;
		return true;
	} else {
		return false;
	}
}

////////////////////////////////////////////////////////////////////////

void testSetAtIndex(void) {
	testSetAtIndexGeneral();
	testSetAtIndexTest1();
	testSetAtIndexTest2();
	testSetAtIndexTest3();
	testSetAtIndexTest4();
	testSetAtIndexTest5();
	testSetAtIndexTest6();
}
void testSetAtIndexGeneral(void) {
	Set s = SetNew();

	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	
	assert(SetAtIndex(s, 0) == 2);
	printf("%d", SetAtIndex(s, 1));
	assert(SetAtIndex(s, 1) == 4);
	assert(SetAtIndex(s, 2) == 5);
	assert(SetAtIndex(s, 3) == 8);

	SetInsert(s, 3);
	assert(SetAtIndex(s, 0) == 2);
	assert(SetAtIndex(s, 1) == 3);
	assert(SetAtIndex(s, 2) == 4);
	assert(SetAtIndex(s, 3) == 5);
	assert(SetAtIndex(s, 4) == 8);

	doBstPrint(s->tree, stdout);
	printf("\n");
	// printf("%d\n", SetAtIndex(s, 1));
	assert(SetAtIndex(s, 0) == 2);
	assert(SetAtIndex(s, 1) == 3);
	assert(SetAtIndex(s, 2) == 4);
	assert(SetAtIndex(s, 3) == 5);
	assert(SetAtIndex(s, 4) == 8);

	SetFree(s);
}

void testSetAtIndexTest1(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 19);
	SetInsert(s, 8);
	SetInsert(s, 15);

	assert(SetAtIndex(s, 0) == 1);
	assert(SetAtIndex(s, 1) == 2);
	assert(SetAtIndex(s, 2) == 4);
	assert(SetAtIndex(s, 3) == 5);
	assert(SetAtIndex(s, 4) == 6);
	assert(SetAtIndex(s, 5) == 7);
	assert(SetAtIndex(s, 6) == 8);
	assert(SetAtIndex(s, 7) == 9);
	assert(SetAtIndex(s, 8) == 11);
	assert(SetAtIndex(s, 9) == 15);
	assert(SetAtIndex(s, 10) == 19);
	SetFree(s);
}
void testSetAtIndexTest2(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 19);
	SetInsert(s, 8);
	SetInsert(s, 15);

	assert(SetAtIndex(s, 0) == 1);
	assert(SetAtIndex(s, 1) == 2);
	assert(SetAtIndex(s, 2) == 4);
	assert(SetAtIndex(s, 3) == 5);
	assert(SetAtIndex(s, 4) == 6);
	assert(SetAtIndex(s, 5) == 7);
	assert(SetAtIndex(s, 6) == 8);
	assert(SetAtIndex(s, 7) == 9);
	assert(SetAtIndex(s, 8) == 11);
	assert(SetAtIndex(s, 9) == 15);
	assert(SetAtIndex(s, 10) == 19);


	SetDelete(s, 11);
	assert(SetAtIndex(s, 0) == 1);
	assert(SetAtIndex(s, 1) == 2);
	assert(SetAtIndex(s, 2) == 4);
	assert(SetAtIndex(s, 3) == 5);
	assert(SetAtIndex(s, 4) == 6);
	assert(SetAtIndex(s, 5) == 7);
	assert(SetAtIndex(s, 6) == 8);
	assert(SetAtIndex(s, 7) == 9);
	assert(SetAtIndex(s, 8) == 15);
	assert(SetAtIndex(s, 9) == 19);
	SetFree(s);
}

void testSetAtIndexTest3(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 19);
	SetInsert(s, 8);
	SetInsert(s, 15);

	assert(SetAtIndex(s, 16) == UNDEFINED);
	
	SetFree(s);
}

void testSetAtIndexTest4(void) {
	Set s = SetNew();

	assert(SetAtIndex(s, 16) == UNDEFINED);
	
	SetFree(s);
}

void testSetAtIndexTest5(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 19);
	SetInsert(s, 8);
	SetInsert(s, 15);

	assert(SetAtIndex(s, -1) == UNDEFINED);
	
	SetFree(s);
}

void testSetAtIndexTest6(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 19);
	SetInsert(s, 8);
	SetInsert(s, 15);

	assert(SetAtIndex(s, 11) == UNDEFINED);
	
	SetFree(s);
}

void testSetIndexOf(void) {
	testSetIndexOfGeneral();
	testSetIndexOfTest1();
	testSetIndexOfTest2();
	testSetIndexOfTest3();
	testSetIndexOfTest4();
}

void testSetIndexOfGeneral(void) {
	Set s = SetNew();

	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	
	assert(SetIndexOf(s, 2) == 0);
	assert(SetIndexOf(s, 4) == 1);
	assert(SetIndexOf(s, 5) == 2);
	assert(SetIndexOf(s, 8) == 3);

	SetInsert(s, 3);

	assert(SetIndexOf(s, 2) == 0);
	assert(SetIndexOf(s, 3) == 1);
	assert(SetIndexOf(s, 4) == 2);
	assert(SetIndexOf(s, 5) == 3);
	assert(SetIndexOf(s, 8) == 4);

	SetFree(s);
}

void testSetIndexOfTest1(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 19);
	SetInsert(s, 8);
	SetInsert(s, 15);

	doBstPrint(s->tree, stdout);

	assert(SetIndexOf(s, 1) == 0);
	assert(SetIndexOf(s, 2) == 1);
	assert(SetIndexOf(s, 4) == 2);
	assert(SetIndexOf(s, 5) == 3);
	assert(SetIndexOf(s, 6) == 4);
	assert(SetIndexOf(s, 7) == 5);
	assert(SetIndexOf(s, 8) == 6);
	assert(SetIndexOf(s, 9) == 7);
	assert(SetIndexOf(s, 11) == 8);
	assert(SetIndexOf(s, 15) == 9);
	assert(SetIndexOf(s, 19) == 10);
	SetFree(s);
}

void testSetIndexOfTest2(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 19);
	SetInsert(s, 8);
	SetInsert(s, 15);

	doBstPrint(s->tree, stdout);

	assert(SetIndexOf(s, 1) == 0);
	assert(SetIndexOf(s, 2) == 1);
	assert(SetIndexOf(s, 4) == 2);
	assert(SetIndexOf(s, 5) == 3);
	assert(SetIndexOf(s, 6) == 4);
	assert(SetIndexOf(s, 7) == 5);
	assert(SetIndexOf(s, 8) == 6);
	assert(SetIndexOf(s, 9) == 7);
	assert(SetIndexOf(s, 11) == 8);
	assert(SetIndexOf(s, 15) == 9);
	assert(SetIndexOf(s, 19) == 10);

	SetDelete(s, 9);
	assert(SetIndexOf(s, 9) == -1);
	SetFree(s);
}

void testSetIndexOfTest3(void) {
	Set s = SetNew();
	assert(SetIndexOf(s, 1) == -1);
	SetFree(s);
}

void testSetIndexOfTest4(void) {
	Set s = SetNew();

	SetInsert(s, 4);
	SetInsert(s, 2);
	SetInsert(s, 5);
	SetInsert(s, 6);
	SetInsert(s, 7);
	SetInsert(s, 1);
	SetInsert(s, 9);
	SetInsert(s, 11);
	SetInsert(s, 19);
	SetInsert(s, 8);
	SetInsert(s, 15);

	doBstPrint(s->tree, stdout);

	assert(SetIndexOf(s, 1) == 0);
	assert(SetIndexOf(s, 2) == 1);
	assert(SetIndexOf(s, 4) == 2);
	assert(SetIndexOf(s, 5) == 3);
	assert(SetIndexOf(s, 6) == 4);
	assert(SetIndexOf(s, 7) == 5);
	assert(SetIndexOf(s, 8) == 6);
	assert(SetIndexOf(s, 9) == 7);
	assert(SetIndexOf(s, 11) == 8);
	assert(SetIndexOf(s, 15) == 9);
	assert(SetIndexOf(s, 19) == 10);
	assert(SetIndexOf(s, '1') == -1);
	assert(SetIndexOf(s, '2') == -1);
	assert(SetIndexOf(s, '3') == -1);
	assert(SetIndexOf(s, '4') == -1);
	assert(SetIndexOf(s, '5') == -1);
	assert(SetIndexOf(s, 'a') == -1);
	assert(SetIndexOf(s, 'b') == -1);
	assert(SetIndexOf(s, 'c') == -1);

	SetDelete(s, 9);
	assert(SetIndexOf(s, 9) == -1);
	SetFree(s);
}
////////////////////////////////////////////////////////////////////////

void testSetCursor1(void) {
	Set s = SetNew();

	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	SetCursor cur = SetCursorNew(s);
	// start  2  4  5  8  end
	//   ^
	assert(SetCursorGet(cur) == UNDEFINED);

	assert(SetCursorNext(cur));
	// start  2  4  5  8  end
	//        ^
	assert(SetCursorGet(cur) == 2);

	assert(SetCursorNext(cur));
	// start  2  4  5  8  end
	//           ^
	assert(SetCursorGet(cur) == 4);

	assert(SetCursorNext(cur));
	// start  2  4  5  8  end
	//              ^
	assert(SetCursorGet(cur) == 5);

	assert(SetCursorNext(cur));
	// start  2  4  5  8  end
	//                 ^
	assert(SetCursorGet(cur) == 8);

	assert(!SetCursorNext(cur));
	// start  2  4  5  8  end
	//                     ^
	assert(SetCursorGet(cur) == UNDEFINED);

	assert(SetCursorPrev(cur));
	// start  2  4  5  8  end
	//                 ^
	assert(SetCursorGet(cur) == 8);

	assert(SetCursorPrev(cur));
	// start  2  4  5  8  end
	//              ^
	assert(SetCursorGet(cur) == 5);

	assert(SetCursorPrev(cur));
	// start  2  4  5  8  end
	//           ^
	assert(SetCursorGet(cur) == 4);

	assert(SetCursorPrev(cur));
	// start  2  4  5  8  end
	//        ^
	assert(SetCursorGet(cur) == 2);

	assert(!SetCursorPrev(cur));
	// start  2  4  5  8  end
	//   ^
	assert(SetCursorGet(cur) == UNDEFINED);

	SetCursorFree(cur);
	SetFree(s);
}

void testSetCursor2(void) {
	Set s = SetNew();

	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	SetCursor cur = SetCursorNew(s);
	// start  2  4  5  8  end
	//   ^
	assert(SetCursorGet(cur) == UNDEFINED);

	assert(SetCursorNext(cur));
	// start  2  4  5  8  end
	//        ^
	assert(SetCursorGet(cur) == 2);

	SetInsert(s, 3);
	// start  2  3  4  5  8  end
	//        ^

	assert(SetCursorNext(cur));
	// start  2  3  4  5  8  end
	//           ^
	assert(SetCursorGet(cur) == 3);

	SetDelete(s, 4);
	// start  2  3  5  8  end
	//           ^

	assert(SetCursorNext(cur));
	// start  2  3  5  8  end
	//              ^
	assert(SetCursorGet(cur) == 5);

	SetCursorFree(cur);
	SetFree(s);
}

////////////////////////////////////////////////////////////////////////
// ASCII tree printer
// Courtesy: ponnada
// Via: http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/

// data structures
typedef struct asciinode_struct asciinode;
struct asciinode_struct {
	asciinode *left, *right;
	// length of the edge from this node to its children
	int edge_length;
	int height;
	int lablen;
	// -1=I am left, 0=I am root, 1=I am right
	int parent_dir;
	// max supported unit32 in dec, 10 digits max
	char label[11];
};

// functions
static void print_level(asciinode *node, int x, int level, FILE *out);
static void compute_edge_lengths(asciinode *node);
static void compute_lprofile(asciinode *node, int x, int y);
static void compute_rprofile(asciinode *node, int x, int y);
static asciinode *build_ascii_tree(struct node *t);
static void free_ascii_tree(asciinode *node);

#define MAX_HEIGHT 1000
static int lprofile[MAX_HEIGHT];
static int rprofile[MAX_HEIGHT];
#define INFINITY (1 << 20)

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

static int gap = 3; // gap between left and right nodes

// used for printing next node in the same level,
// this is the x coordinate of the next char printed
static int print_next;

// prints ascii tree for given Tree structure
void doBstPrint(struct node *t, FILE *out)
{
	asciinode *proot;
	int xmin, i;
	if (t == NULL)
		return;
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		lprofile[i] = INFINITY;
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		xmin = MIN(xmin, lprofile[i]);
	for (i = 0; i < proot->height; i++) {
		print_next = 0;
		print_level(proot, -xmin, i, out);
		fprintf(out, "\n");
	}
	if (proot->height >= MAX_HEIGHT) {
		fprintf(out,
			"(Tree is taller than %d; may be drawn incorrectly.)\n",
			MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}

// This function prints the given level of the given tree, assuming
// that the node has the given x cordinate.
static void print_level(asciinode *node, int x, int level, FILE *out)
{
	int i, isleft;
	if (node == NULL)
		return;
	isleft = (node->parent_dir == -1);
	if (level == 0) {
		for (i = 0;
			 i < (x - print_next - ((node->lablen - isleft) / 2));
			 i++)
			fprintf(out, " ");
		print_next += i;
		fprintf(out, "%s", node->label);
		print_next += node->lablen;
	} else if (node->edge_length >= level) {
		if (node->left != NULL) {
			for (i = 0; i < (x - print_next - (level)); i++) {
				fprintf(out, " ");
			}
			print_next += i;
			fprintf(out, "/");
			print_next++;
		}
		if (node->right != NULL) {
			for (i = 0; i < (x - print_next + (level)); i++) {
				fprintf(out, " ");
			}
			print_next += i;
			fprintf(out, "\\");
			print_next++;
		}
	} else {
		print_level(
			node->left,
			x - node->edge_length - 1,
			level - node->edge_length - 1,
			out);
		print_level(
			node->right,
			x + node->edge_length + 1,
			level - node->edge_length - 1,
			out);
	}
}

// This function fills in the edge_length and
// height fields of the specified tree
static void compute_edge_lengths(asciinode *node)
{
	int h, hmin, i, delta;
	if (node == NULL)
		return;
	compute_edge_lengths(node->left);
	compute_edge_lengths(node->right);

	/* first fill in the edge_length of node */
	if (node->right == NULL && node->left == NULL)
		node->edge_length = 0;
	else {
		if (node->left == NULL)
			hmin = 0;
		else {
			for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
				rprofile[i] = -INFINITY;
			compute_rprofile(node->left, 0, 0);
			hmin = node->left->height;
		}
		if (node->right == NULL)
			hmin = 0;
		else {
			for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
				lprofile[i] = INFINITY;
			compute_lprofile(node->right, 0, 0);
			hmin = MIN(node->right->height, hmin);
		}
		delta = 4;
		for (i = 0; i < hmin; i++) {
			int w = gap + 1 + rprofile[i] - lprofile[i];
			delta = (delta > w) ? delta : w;
		}

		// If the node has two children of height 1, then we allow the
		// two leaves to be within 1, instead of 2
		if (((node->left != NULL && node->left->height == 1) ||
			(node->right != NULL && node->right->height == 1)) &&
			delta > 4)
			delta--;
		node->edge_length = ((delta + 1) / 2) - 1;
	}

	// now fill in the height of node
	h = 1;
	if (node->left != NULL)
		h = MAX(node->left->height + node->edge_length + 1, h);
	if (node->right != NULL)
		h = MAX(node->right->height + node->edge_length + 1, h);
	node->height = h;
}

static asciinode *build_ascii_tree_recursive(struct node *t)
{
	asciinode *node;

	if (t == NULL)
		return NULL;
	node = malloc(sizeof(asciinode));
	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);
	if (node->left != NULL)
		node->left->parent_dir = -1;
	if (node->right != NULL)
		node->right->parent_dir = 1;
	sprintf(node->label, "%d", t->item);
	node->lablen = (int) strlen(node->label);

	return node;
}

// Copy the tree into the ascii node structre
static asciinode *build_ascii_tree(struct node *t)
{
	asciinode *node;
	if (t == NULL)
		return NULL;
	node = build_ascii_tree_recursive(t);
	node->parent_dir = 0;
	return node;
}

// Free all the nodes of the given tree
static void free_ascii_tree(asciinode *node)
{
	if (node == NULL)
		return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

// The following function fills in the lprofile array for the given
// tree. It assumes that the center of the label of the root of this tree
// is located at a position(x,y).  It assumes that the edge_length
// fields have been computed for this tree.
static void compute_lprofile(asciinode *node, int x, int y)
{
	int i, isleft;
	if (node == NULL)
		return;
	isleft = (node->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
	if (node->left != NULL) {
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
			lprofile[y + i] = MIN(lprofile[y + i], x - i);
	}
	compute_lprofile(
		node->left,
		x - node->edge_length - 1,
		y + node->edge_length + 1);
	compute_lprofile(
		node->right,
		x + node->edge_length + 1,
		y + node->edge_length + 1);
}

static void compute_rprofile(asciinode *node, int x, int y)
{
	int i, notleft;
	if (node == NULL)
		return;
	notleft = (node->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
	if (node->right != NULL) {
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
			rprofile[y + i] = MAX(rprofile[y + i], x + i);
	}
	compute_rprofile(
		node->left,
		x - node->edge_length - 1,
		y + node->edge_length + 1);
	compute_rprofile(
		node->right,
		x + node->edge_length + 1,
		y + node->edge_length + 1);
}

