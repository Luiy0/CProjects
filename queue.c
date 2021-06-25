/* queue.c
 * By Luis A. Flores (841102500)
 * 11/1/2015
 * This file contains the private implementation of a queue using a linked list.
 */

#include "queue.h"   // for queue and its functions
#include <stdlib.h>  // for malloc and free
#include <stddef.h>  // for NULL definition

// Defines Node as an alias for the node structure.
typedef struct node Node;

// Declares a structure for nodes.
struct node {
    void *data;
    Node *next;
};
// Defines the queue structure.
struct queue {
    Node *front;        // pointer to the first node
    Node *rear;         // pointer to the last node
};

// Returns a new empty queue.
Queue *create_queue(void){
    Queue *que = malloc(sizeof(Queue));
    que->front = que->rear = NULL;
    return que;
}

// Determines whether the queue is empty.
bool is_empty_queue(const Queue *que){
    return que->front == NULL;
}

// Adds an element to the rear of the queue.
void enqueue(Queue *que, const void *elem){
     Node *temp = malloc(sizeof(Node));
     temp->data = elem;
     temp->next=NULL;

     if(is_empty_queue(que)){
        que->front = temp;
        que->rear = temp;
     }
     else{
        que->rear->next = temp;
        que->rear = temp;
    }
}

// Removes and returns the element at the front of the queue.
// Returns NULL if queue is empty.
void *dequeue(Queue *que){
    if(is_empty_queue(que))
        return NULL;
    else{
        void *elem = que->front->data;
        que->front = que->front->next;
        return elem;
    }
}

// Iterates through the queue using a visit function.
void iterate_queue(const Queue *que, void (*visit)(const void *elem)){
     for (Node *curr = que->front; curr != NULL; curr = curr->next)
        visit(curr->data);
}

// Deallocates the memory of the queue.
void destroy_queue(Queue *que){
     for (Node *curr = que->front; curr != NULL; curr = curr->next) {
        curr = que->front;
        que->front = curr->next;
        free(curr);
    }
    free(que);
}




