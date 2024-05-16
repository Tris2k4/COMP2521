// Implementation of the Set ADT
// COMP2521 - Assignment 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Set.h"
#include "SetStructs.h"

////////////////////////////////////////////////////////////////////////
// Function prototype
static void setFreeHelper(struct node *t);
static struct node *setInsertHelper(Set s, struct node *t, int item);
static struct node *newNode(int value);
static struct node *setDeleteHelper(Set s, struct node *t, int item);
static bool setContainsHelper(struct node *t, int item);
static void setPrintHelper(struct node *t, FILE *out, int *first);
static void setUnionHelper(Set s3, struct node *t);
static void setUnionInsertHelper(Set s, struct node *t);
static struct node *setIntersectionInsertHelper(Set s, Set s1, struct node *t2);
static bool SetEqualsHelper(struct node *t, Set s);
static bool setSubsetHelper(struct node *t, Set s);
static int max(int a, int b);
static int height(struct node *t);
static struct node *rotateLeft(struct node *root);
static struct node *rotateRight(struct node *root);
static struct node *avlRebalance(struct node *t);
static int balance(struct node *t);
static int count(struct node *t);
static int setAtIndexHelper(struct node *t, int k);
static int SetIndexOfHelper(struct node *t, int elem, int index);
////////////////////////////////////////////////////////////////////////

// Basic Set Operations

/**
 * Creates a new empty set
 */
Set SetNew(void)
{
    // TODO
    Set s = malloc(sizeof(struct set));
    if (!s)
    {
        return NULL;
    }
    s->tree = NULL;
    s->size = 0;
    return s;
}

/**
 * Frees all memory allocated to the set
 */
void SetFree(Set s)
{
    // TODO
    if (!s)
    {
        return;
    }
	// call helper function to delete each node in the tree
    setFreeHelper(s->tree);
    free(s);
}

static void setFreeHelper(struct node *t)
{
    if (!t)
    {
        return;
    }
    setFreeHelper(t->left);
    setFreeHelper(t->right);
    free(t);
}

/**
 * Inserts an item into the set
 */
void SetInsert(Set s, int item)
{
    // TODO
    if (item == UNDEFINED)
    {
        return;
    }
    if (!s->tree)
    {
        s->tree = setInsertHelper(s, s->tree, item);
    }
    else
    {
        s->tree = setInsertHelper(s, s->tree, item);
    }
}

static struct node *setInsertHelper(Set s, struct node *t, int item)
{	
	// if t is null then create a new node
    if (!t)
    {
        s->size++;
        return newNode(item);
    }
	// if we found duplicate item then we just need to return and not insert
    if (t->item == item)
    {
        return t;
    }
	// smaller item will go to the left
    if (item < t->item)
    {
        t->left = setInsertHelper(s, t->left, item);
    }
	// bigger item will go to the right
    if (item > t->item)
    {
        t->right = setInsertHelper(s, t->right, item);
    }
	// calculate the height of the tree and store the height into each node
	t->height = max(height(t->left), height(t->right)) + 1;
	
	// count the total number of nodes in the left and right subtree
    t->count = 1 + count(t->left) + count(t->right);
    int leftHeight = height(t->left);
    int rightHeight = height(t->right);


    if (leftHeight - rightHeight > 1)
    {
        if (item > t->left->item)
        {
            t->left = rotateLeft(t->left);
        }
        t = rotateRight(t);
        return t;
    }

    if (rightHeight - leftHeight > 1)
    {
        if (item < t->right->item)
        {
            t->right = rotateRight(t->right);
        }
        t = rotateLeft(t);
        return t;
    }
    return t;
}

static struct node *newNode(int value)
{
    struct node *newNode = malloc(sizeof(struct node));
    if (!newNode)
    {
        return NULL;
    }
    newNode->item = value;
    newNode->left = newNode->right = NULL;
    newNode->height = 0;
    newNode->count = 1;
    return newNode;
}
// function to find the max
static int max(int a, int b)
{
    return (a > b ? a : b);
}
// function to calculate the height of the tree
static int height(struct node *t)
{
    return (!t ? -1 : t->height);
}

static struct node *rotateLeft(struct node *root)
{
    if (!root)
    {
        return NULL;
    }
    if (!root->left && !root->right)
    {
        return root;
    }
    if (!root->right)
    {
        return root;
    }
	// start performing rotation
    struct node *newRoot = root->right;
    struct node *child = newRoot->left;

    newRoot->left = root;
    root->right = child;
	
	// recalculate the height after rotation
    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
	
	// recalculate the count after rotation
    root->count = 1 + count(root->left) + count(root->right);
    newRoot->count = 1 + count(newRoot->left) + count(newRoot->right);
    return newRoot;
}

static struct node *rotateRight(struct node *root)
{
    if (!root)
    {
        return NULL;
    }
    if (!root->left && !root->right)
    {
        return root;
    }
    if (!root->left)
    {
        return root;
    }

    struct node *newRoot = root->left;
    struct node *child = newRoot->right;
	// perform rotation
    newRoot->right = root;
    root->left = child;

	// recalculate the height after rotation
    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
	
	// recalculate the count after rotation
    root->count = 1 + count(root->left) + count(root->right);
    newRoot->count = 1 + count(newRoot->left) + count(newRoot->right);
    return newRoot;
}

// count function to help calculate the number of nodes in the left and right subtree
static int count(struct node *t)
{
    return (!t ? 0 : t->count);
}

/**
 * Deletes an item from the set
 */
void SetDelete(Set s, int item)
{
    // TODO
    if (!s || item == UNDEFINED)
    {
        return;
    }
    s->tree = setDeleteHelper(s, s->tree, item);
}

static struct node *setDeleteHelper(Set s, struct node *t, int item)
{
    if (!t)
    {
        return NULL;
    }
    if (item < t->item)
    {
        t->left = setDeleteHelper(s, t->left, item);
    }
    else if (item > t->item)
    {
        t->right = setDeleteHelper(s, t->right, item);
    }
    else
    {	
		// Case1: leaf node
        if (!t->left && !t->right)
        {
            s->size--;
            free(t);
            return NULL;
        }
		// Case2: there is no left subtree
        if (!t->left)
        {
            struct node *temp = t->right;
            s->size--;
            free(t);
            return temp;
        }
		// Case3: there is no right subtree
        if (!t->right)
        {
            struct node *temp = t->left;
            s->size--;
            free(t);
            return temp;
        }
		// Case4: there are left and right subtree
        else
        {
            struct node *successor = t->right;
            while (successor->left)
            {
                successor = successor->left;
            }
            t->item = successor->item;
            t->right = setDeleteHelper(s, t->right, successor->item);
        }
    }
	// balance the tree after rotation
    return avlRebalance(t);
}

// Implementation of delete a node in an avl tree
// This file was taken from 
// https://cgi.cse.unsw.edu.au/~cs2521/24T1/lectures/slides/week04tue-avl-trees.pdf
static struct node *avlRebalance(struct node *t)
{
    if (!t)
    {
        return NULL;
    }

    int bal = balance(t);
    if (bal > 1)
    {
        if (balance(t->left) < 0)
        {
            t->left = rotateLeft(t->left);
        }
        t = rotateRight(t);
    }
    if (bal < -1)
    {
        if (balance(t->right) > 0)
        {
            t->right = rotateRight(t->right);
        }
        t = rotateLeft(t);
    }

    return t;
}

// calculate the balance of the tree
static int balance(struct node *t)
{
    return (!t ? 0 : height(t->left) - height(t->right));
}

/**
 * Returns the number of elements in the set
 */
int SetSize(Set s)
{
    // TODO
    return s->size;
}

/**
 * Returns true if the set contains the given item, and false otherwise
 */
bool SetContains(Set s, int item)
{
    // TODO
    return (!s->tree || item == UNDEFINED ? false : setContainsHelper(s->tree, item));
}

static bool setContainsHelper(struct node *t, int item)
{
    if (!t)
    {
        return false;
    }
    if (item == t->item)
    {
        return true;
    }
    if (item < t->item)
    {
        return setContainsHelper(t->left, item);
    }
    if (item > t->item)
    {
        return setContainsHelper(t->right, item);
    }
    return false; // return false if item not found
}

/**
 * Prints the elements in the set to the given file in ascending order
 * between curly braces, with items separated by a comma and space
 */
void SetPrint(Set s, FILE *out)
{
	// if the set is empty then print {}
    if (!s)
    {
        fprintf(out, "{}");
    }
    else
    {
        fprintf(out, "{");
        int first = 1; // create first to print the first number
        setPrintHelper(s->tree, out, &first);
        fprintf(out, "}");
    }
}

static void setPrintHelper(struct node *t, FILE *out, int *first)
{
    if (!t)
    {
        return;
    }
    setPrintHelper(t->left, out, first);
    if (*first)
    {
        fprintf(out, "%d", t->item);
        *first = 0;
    }
    else
    {
        fprintf(out, ", %d", t->item);
    }
    setPrintHelper(t->right, out, first);
}

////////////////////////////////////////////////////////////////////////
// Common Set Operations

/**
 * Returns a new set representing the union of the two sets
 */
Set SetUnion(Set s1, Set s2)
{
    // TODO
    Set s3 = SetNew();
    if (!s3)
    {
        return NULL;
    }
    setUnionHelper(s3, s1->tree);
    setUnionInsertHelper(s3, s2->tree);
    return s3;
}

// insert all items from set 1 to set 3
static void setUnionHelper(Set s3, struct node *t)
{
    if (!t)
    {
        return;
    }
    setUnionHelper(s3, t->left);
    setUnionHelper(s3, t->right);
    SetInsert(s3, t->item);
}

// search item in set 2 and if it is not in set 3 then insert into set 3
static void setUnionInsertHelper(Set s, struct node *t)
{
    if (!t)
    {
        return;
    }
	// if item not found then insert
    if (!SetContains(s, t->item))
    {
        SetInsert(s, t->item);
    }
    setUnionInsertHelper(s, t->left);
    setUnionInsertHelper(s, t->right);
}

/**
 * Returns a new set representing the intersection of the two sets
 */

Set SetIntersection(Set s1, Set s2)
{
    // TODO
    Set s3 = SetNew();
    if (!s3)
    {
        return NULL;
    }
    setIntersectionInsertHelper(s3, s1, s2->tree);
    return s3;
}

static struct node *setIntersectionInsertHelper(Set s, Set s1, struct node *t2)
{
    if (!t2)
    {
        return NULL;
    }
	//if there is an item in both set 1 and 2 then insert
    if (SetContains(s1, t2->item))
    {
        SetInsert(s, t2->item);
    }
    setIntersectionInsertHelper(s, s1, t2->left);
    setIntersectionInsertHelper(s, s1, t2->right);
    return t2;
}

/**
 * Returns true if the two sets are equal, and false otherwise
 */
bool SetEquals(Set s1, Set s2)
{
    // TODO
	// return false if the size of 2 sets are not equal, otherwise we will check both sets
    return (SetSize(s1) != SetSize(s2) ? false : SetEqualsHelper(s1->tree, s2));
}

static bool SetEqualsHelper(struct node *t, Set s)
{
    if (!t)
    {
        return true;
    }
	//if item not found which means not equal then return false
    if (!SetContains(s, t->item))
    {
        return false;
    }
    return SetEqualsHelper(t->left, s) && SetEqualsHelper(t->right, s);
}

/**
 * Returns true if set s1 is a subset of set s2, and false otherwise
 */
bool SetSubset(Set s1, Set s2)
{
    // TODO
	//if the size of set 1 is less than or equal to set 2 
	//then we will traverse the set 1 tree, otherwise we will traverse set 2 tree
    return (SetSize(s1) <= SetSize(s2) 
            ? setSubsetHelper(s1->tree, s2) : setSubsetHelper(s2->tree, s1));
}

static bool setSubsetHelper(struct node *t, Set s)
{
    if (!t)
    {
        return true;
    }
	// if item not found then return false
    if (!SetContains(s, t->item))
    {
        return false;
    }
    return setSubsetHelper(t->left, s) && setSubsetHelper(t->right, s);
}

////////////////////////////////////////////////////////////////////////
// Index Operations

/**
 * Returns the element at the given index, or UNDEFINED if the given
 * index is outside the range [0, n - 1] where n is the size of the set
 */

int SetAtIndex(Set s, int index)
{
    // TODO
    return (index > SetSize(s) - 1 || index < 0 ||
            !s || index == UNDEFINED 
                ? UNDEFINED : setAtIndexHelper(s->tree, index + 1));
}

static int setAtIndexHelper(struct node *t, int k)
{
    if (!t)
    {
        return UNDEFINED;
    }
	// calculate the left size of the subtree
    int leftCount = count(t->left);
	// if k equals to the amount of left count + 1 which means we will return the item sinced it founned
    if (k == leftCount + 1)
    {
        return t->item;
    }
	// if k is less than the left count then we will traverse left
    if (k < leftCount + 1)
    {
        return setAtIndexHelper(t->left, k);
    }
	// otherwise go right
    return setAtIndexHelper(t->right, k - leftCount - 1);
}

/**
 * Returns the index of the given element in the set if it exists, and
 * -1 otherwise
 */

int SetIndexOf(Set s, int elem)
{
    // TODO
    return (!s || elem == UNDEFINED ? -1 : SetIndexOfHelper(s->tree, elem, 0));
}

static int SetIndexOfHelper(struct node *t, int elem, int index)
{
    if (!t)
    {
        return -1;
    }
	// if item found then return the index;
    if (elem == t->item)
    {
        return index + count(t->left);
    }
    if (elem < t->item)
    {
        return SetIndexOfHelper(t->left, elem, index);
    }
    return SetIndexOfHelper(t->right, elem, index + count(t->left) + 1);
}

////////////////////////////////////////////////////////////////////////
// Cursor Operations

/**
 * Creates a new cursor positioned at the *start* of the set
 * (see the spec for details)
 */
SetCursor SetCursorNew(Set s)
{
    // TODO
    return NULL;
}

/**
 * Frees all memory allocated to the given cursor
 */
void SetCursorFree(SetCursor cur)
{
    // TODO
}

/**
 * Returns the element at the cursor's position, or UNDEFINED if the
 * cursor is positioned at the *start* or *end* of the set
 */
int SetCursorGet(SetCursor cur)
{
    // TODO
    return UNDEFINED;
}

/**
 * Moves the cursor to the next greatest element, or to the end of the
 * set if there is no next greatest element. Does not move the cursor if
 * it is already at the end. Returns false if the cursor is at the end
 * after this operation, and true otherwise.
 */
bool SetCursorNext(SetCursor cur)
{
    // TODO
    return false;
}

/**
 * Moves the cursor to the next smallest element, or to the start of the
 * set if there is no next smallest element. Does not move the cursor if
 * it is already at the start. Returns false if the cursor is at the
 * start after this operation, and true otherwise.
 */
bool SetCursorPrev(SetCursor cur)
{
    // TODO
    return false;
}

////////////////////////////////////////////////////////////////////////
