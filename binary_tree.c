/*
 * binary_tree.c
 * By Antonio F. Huertas & Luis A. Flores (841102500)
 * 10/31/2015
 * This program defines and manipulates a binary search tree.
 */

#include <stdio.h>   // for puts, printf, scanf
#include <stdbool.h> // for bool, true, false
#include <stddef.h>  // for NULL
#include <stdlib.h>  // for malloc, free

// Defines an alias for the node structure.
typedef struct node Node;

// Declares a structure for nodes.
struct node {
    int data;
    Node *left, *right;
};

// Declares the data structure for a binary tree.
typedef struct {
    Node *root;
} Tree;

// Declares functions using prototypes.
Tree *create_tree(void);
void add_tree(Tree *bst, int val);
void show_tree(const Tree *bst);
int sum_tree(const Tree *bst);
bool search_tree(const Tree *bst, int val);
void destroy_tree(Tree *bst);

Node *add_helper(Node *curr, int val);
void show_helper(const Node *curr);
int sum_helper(const Node *curr);
bool search_helper(Node *curr, int val);
void destroy_helper(Node *curr);

int size_helper(const Node *curr);
int depth_helper(Node *curr);
int min_helper(Node *curr);

int size_tree(const Tree *bst);
int depth_tree(const Tree *bst);
int minimum_tree(const Tree *bst);

// Starts the execution of the program.
int main(void) {
    Tree *bst = create_tree();
    puts("A binary search tree has been created.");

    add_tree(bst, 40);
    add_tree(bst, 10);
    add_tree(bst, 20);
    add_tree(bst, 50);
    add_tree(bst, 30);

    printf("After adding some elements, the tree is ");
    show_tree(bst);
    printf("\nThe sum of its elements is %d\n", sum_tree(bst));
    printf("\n");

    int num;
    printf("Enter a number to be searched: ");
    scanf("%d", &num);

    bool found = search_tree(bst, num);
    if (found)
        puts("The number was found!");
    else
        puts("The number was NOT found.");

    printf("\nEnter a number to be added to the tree: ");
    scanf("%d", &num);
    add_tree(bst, num);

    printf("After adding a new element, the tree is ");
    show_tree(bst);
    printf("\n\nThe sum of its elements is %d\n", sum_tree(bst));

    printf("The size of the tree is: %d\n",size_tree(bst));
    printf("The depth of the tree is: %d\n",depth_tree(bst));
    printf("The minimum element of the tree is: %d\n",minimum_tree(bst));
    printf("\n");

    destroy_tree(bst);
    bst = NULL;
    puts("The binary search tree has been deallocated.");
    return 0;
}

// Returns a new empty tree.
Tree *create_tree(void) {
    Tree *bst = malloc(sizeof(Tree));
    bst->root = NULL;
    return bst;
}

// Adds a new value to the given tree.
void add_tree(Tree *bst, int val) {
    bst->root = add_helper(bst->root, val);
}

Node *add_helper(Node *curr, int val) {
    if (curr == NULL) {
        curr = malloc(sizeof(Node));
        curr->data = val;
        curr->left = curr->right = NULL;
    } else {
        if (val < curr->data)
            curr->left = add_helper(curr->left, val);
        else if (val > curr->data)
            curr->right = add_helper(curr->right, val);
        else
            curr->data = val;
    }
    return curr;
}

// Shows the contents of the given tree.
void show_tree(const Tree *bst) {
    show_helper(bst->root);
}

void show_helper(const Node *curr) {
    if (curr != NULL) {
        show_helper(curr->left);
        printf("%d ", curr->data);
        show_helper(curr->right);
    }
}

// Returns the sum of the given tree.
int sum_tree(const Tree *bst) {
    return sum_helper(bst->root);
}

int sum_helper(const Node *curr) {
    if (curr == NULL)
        return 0;
    else
        return sum_helper(curr->left) + curr->data + sum_helper(curr->right);
}

// Determines whether the given tree contains the given value.
bool search_tree(const Tree *bst, int val) {
    return search_helper(bst->root, val);
}

bool search_helper(Node *curr, int val) {
    if (curr == NULL)
        return false;
    else {
        if (val < curr->data)
            return search_helper(curr->left, val);
        else if (val > curr->data)
            return search_helper(curr->right, val);
        else
            return true;
    }
}

// Frees the memory allocated for the tree.
void destroy_tree(Tree *bst) {
    destroy_helper(bst->root);
    free(bst);
}

void destroy_helper(Node *curr) {
    if (curr != NULL) {
        destroy_helper(curr->left);
        destroy_helper(curr->right);
        free(curr);
    }
}

// Returns the number of elements in a tree.
int size_tree(const Tree *bst) {
    return size_helper(bst->root);
}

int size_helper(const Node *curr) {
    if (curr == NULL)
        return 0;
    else
        return 1 + size_helper(curr->left) + size_helper(curr->right);
}

// Returns the depth or levels of the tree.
int depth_tree(const Tree *bst){
    return depth_helper(bst->root);
}

int depth_helper( Node *curr){
    if(curr == NULL)
        return 0;
    else
        return (depth_helper(curr->left) > depth_helper(curr->right))? depth_helper(curr->left)+1 : depth_helper(curr->right)+1;
        // check
}

// Returns the minimum element of a tree
int minimum_tree(const Tree *bst) {
    return min_helper(bst->root);
}

int min_helper(Node *curr) {
    while (curr->left != NULL)
        curr = curr->left;
    return(curr->data);
}
