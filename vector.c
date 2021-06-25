/* vectorArray.c
 * By Luis A. Flores (841102500)
 * 10/30/2015 to 11/2/2015
 * Source file for a generic vector implemented using an array.
 */

#include "vector.h" // for Vector and its functions
#include <stdlib.h>  // for malloc and free
#include <stddef.h>  // for NULL definition

// Defines the vector structure
struct vector {
    int capacity;
    void **data; // pointer to an array of void pointers
    int size;
};

// Returns a new empty vector with the specified initial capacity.
// Pre: init_cap > 0
Vector *create_vector(int init_cap){
    if(init_cap > 0){
        Vector *vct = malloc(sizeof(Vector));
        vct->capacity = init_cap;
        vct->data = malloc(vct->capacity * sizeof(void *));
        vct->size = 0;
        return vct;
    }
    exit(1);
}

// Adds an element at the end of the vector.
void add_vector(Vector *vct, const void *elem){
//  vct->data[vct->size] = elem;   Warning: assignment discards 'const' qualifier from point target type.
    vct->data[vct->size] = (char *)elem;
    vct->capacity--;
    vct->size++;
}

// Returns the number of elements in the vector.
int size_vector(const Vector *vct){return vct->size;}

// Changes the element at the specified index of the vector.
// Pre: idx >= 0 && idx < size_vector.
bool set_vector(Vector *vct, int idx, const void *elem){
    if (idx < 0 || idx >= size_vector(vct))
        return false;
    else{
        vct->data[idx] = (char *)elem;
        return true;
    }
}

// Returns the element at the given index of the vector.
// Returns NULL if idx < 0 || idx >= size_vector(vct).
void *get_vector(const Vector *vct, int idx){
    if(idx < 0 || idx >= size_vector(vct))
        return NULL;
    else
        return vct->data[idx];
}

// Inserts an element at the given index of the vector and returns a success indicator.
// Returns false if idx < 0 || idx > size_vector(vct).
bool insert_vector(Vector *vct, int idx, const void *elem){
    if(idx < 0 || idx > size_vector(vct))
        return false;
    else{
        Vector *temp = create_vector(10);  // Memory efficient?
        // Other logic: Create a temporary pointer to an array of void pointers instead of a vector
        // temp will have the vector elements including the element to be inserted (until curr == idx)
        // Assign the other elements of vct to temp (Didn't work)
        // vct->data = temp

        for(int curr = 0; curr <= idx; curr++)
            if(curr != idx)
                add_vector(temp, vct->data[curr]);
            else
                add_vector(temp, elem);

        for(int x = idx; x < vct->size; x++)
            add_vector(temp, vct->data[x]);

    free(vct->data);
    vct->data = temp->data;
    vct->size++;
    free(temp);
    }
    return true;
}

// Removes and returns the element at the given index of the vector.
// Returns NULL if idx < 0 || idx >= size_vector(vct).
void *remove_vector(Vector *vct, int idx){
    void *holder = vct->data[idx];
    if(idx < 0 || idx >= size_vector(vct))
        return NULL;
    else{
        Vector *temp = create_vector(10);
        for(int curr = 0; curr < vct->size; curr++)
            if(curr != idx)
                add_vector(temp, vct->data[curr]);

        free(vct->data);
        vct->data = temp->data;
        vct->size--;
        free(temp);
    }
    return holder;
}

// Returns the index of the given element in the vector, if found.
// Returns -1 otherwise.  It performs a sequential search.
int find_vector(const Vector *vct, const void *elem, int (*compare)(const void *a, const void *b)){
    //strcmp returns 0 if both strings are equal.
    for (int idx = 0; idx < vct->size; idx++)
        if((*compare)(elem, vct->data[idx]) == 0)
            return idx;
    return -1;
}

// Returns the index of the given element in the vector, if found.
// Returns -1 otherwise.  It performs a binary search.
// Pre: The given vector is sorted.
int binary_search_vector(const Vector *vct, const void *elem, int (*compare)(const void *a, const void *b)){
    int lo = 0, hi = vct->size;
    while(lo <= hi){
        int mid = (lo + hi)/2;
        if((*compare)(elem, vct->data[mid]) < 0)
            hi = mid - 1;
        else if ((*compare)(elem, vct->data[mid]) > 0)
            lo = mid + 1;
        else
            return mid;
    }
    return -1;
}

// Sorts the given vector using insertion sort algorithm.
void sort_vector(Vector *vct, int (*compare)(const void *a, const void *b)){
    int pos;
    void *temp;
    for(int idx = 1; idx < vct->size; idx++){
        temp = vct->data[idx];
        pos = idx - 1;
        while(pos >= 0 && ((*compare)(vct->data[pos], temp)) > 0){
            vct->data[pos+1] = vct->data[pos];
            pos = pos - 1;
        }
        vct->data[pos+1] = temp;
    }
}

// Iterates through the vector using a visit function.
void iterate_vector(const Vector *vct, void (*visit)(const void *elem)){
    for (int idx = 0; idx < vct->size ; idx++)
        (*visit)(vct->data[idx]);
}

// Deallocates the memory of the vector.
void destroy_vector(Vector *vct){
    free(vct->data);
    free(vct);
}


