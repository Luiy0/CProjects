/*
 * binary_tree.c
 * By Antonio F. Huertas & Luis A. Flores (841102500)
 * 10/31/2015
 * This program defines and manipulates a binary search tree.
 */

#include <stdio.h>   // for puts, printf, scanf
#include <stdbool.h> // for bool, true, false
#include <stddef.h>  // for NULL
#include <stdlib.h>  // for malloc, free, rand
#include <time.h>

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
bool search_tree(const Tree *bst, int val);
void destroy_tree(Tree *bst);

Node *add_helper(Node *curr, int val);
void show_helper(const Node *curr);
bool search_helper(Node *curr, int val);
void destroy_helper(Node *curr);


// Starts the execution of the program.
int main(void) {
    Tree *bst = create_tree();

    int elements;
    printf("Enter the number of elements in the sequence: ");
    scanf("%d", &elements);

    srand(time(NULL));
    for(int x=0; x<elements; x++)
        add_tree(bst, rand() %100);

    printf("This is the sequence: ");
    show_tree(bst);

    Tree *temp = create_tree();
    int duplicates = findDuplicate(bst, temp);
    printf("\nThe number of pairs is: " + duplicates);

    destroy_tree(bst);
    bst = NULL;
    return 0;

}

int findDuplicate(Tree *curr, Tree *prev) {
    if(curr == NULL)
        return 0;
    else {
        int count = 0;
		if(curr->root->data == prev->root->data)
            count++;
        return count + findDuplicate(curr->root->left, curr) + findDuplicate(curr->root->right, curr);
    }
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

