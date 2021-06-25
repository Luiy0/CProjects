/* array_demo.c
 * By Antonio F. Huertas and Luis A. Flores (841102500)
 * 10/12/2015
 * This program defines some basic array functions.
 */

#include <stdio.h>    // for printf, scanf
#define LENGTH 5      // Defines a symbolic constant

// Declares functions using prototypes.
void read_array(int *arr, int len);
void show_array(const int *arr, int len);
int sum_array(const int *arr, int len);
void insertion_sort(int arr[], int len, int (*compare)(int a, int b));
int binary_search(int key, const int arr[], int len, int (*compare)(int a, int b));
int linear_search(int key, const int arr[], int len);
void selection_sort(int arr[], int len, int (*compare)(int val1, int val2));

int ascending(int a, int b);
int descending(int a, int b);

// Starts the execution of the program.
int main(void) {
    int arr1[LENGTH];

    printf("Enter %d elements for arr1: ", LENGTH);
    read_array(arr1, LENGTH);
    printf("\n");

    printf("This is arr1: ");
    show_array(arr1, LENGTH);

    printf("The sum of its elements is %d\n",
           sum_array(arr1, LENGTH));
    printf("\n");

    insertion_sort(arr1, LENGTH, &ascending);
    printf("This is arr1, sorted in ascending order using insertion sort: ");
    show_array(arr1, LENGTH);

    int value;
    printf("Enter a value to search: ");
    scanf("%d", &value);

    int index = binary_search(value, arr1, LENGTH, &ascending);
    if (index == -1)
        printf("\nThe value was not found.\n");
    else
        printf("The value was found using binary search at index #%d\n", index);
    printf("\n");

    selection_sort(arr1, LENGTH, &descending);
    printf("This is arr1, sorted in descending order using selection sort: ");
    show_array(arr1, LENGTH);

    index = linear_search(value, arr1, LENGTH);
    if (index == -1)
        printf("\nThe value was not found.\n");
    else
        printf("The value was found using linear search at index #%d\n", index);

    printf("\nEnter a value to search: ");
    scanf("%d", &value);

    index = linear_search(value, arr1, LENGTH);
    if (index == -1)
        printf("The value was not found.\n");
    else
        printf("The value was found using linear search at index #%d\n", index);
    printf("\n");

    int order;
    printf("How would you like to order the array? ascending(1), descending(2):");
    if(scanf("%d", &order) == 0){
        printf("Invalid selection.\n");
        exit(0);
    }

    if(order == 1){
        selection_sort(arr1, LENGTH, &ascending);
        printf("This is arr1, sorted in ascending order using selection sort: ");
        show_array(arr1, LENGTH);
        printf("\n");
    }
    else if(order == 2){
        selection_sort(arr1, LENGTH, &descending);
        printf("This is arr1, sorted in descending order using selection sort: ");
        show_array(arr1, LENGTH);
        printf("\n");
    }
    else{
        printf("Invalid selection.\n");
        exit(0);
    }

    printf("Thank you.\n");
    return 0;
}

// Reads the contents of the given array.
void read_array(int *arr, int len) {
    for (int idx = 0; idx < len; idx++)
        scanf("%d", arr + idx);
}

// Displays the contents of the given array.
void show_array(const int *arr, int len) {
    for (int idx = 0; idx < len; idx++)
        printf("%d ", *(arr + idx));
    printf("\n");
}

// Returns the sum of the elements in the given array.
int sum_array(const int *arr, int len) {
    int sum = 0;
    for (int idx = 0; idx < len; idx++)
        sum += arr[idx];   // alt.: sum += *(arr + idx);
    return sum;
}

// Sorts the elements of the given array using the insertion sort algorithm.
void insertion_sort(int arr[], int len, int (*compare)(int a, int b)) {
    for (int idx = 1; idx < len; idx++) {
        int  temp = arr[idx], pos = idx;
        int cmp = (*compare)(arr[pos - 1], temp);
        while (pos > 0 && cmp > 0) {
            arr[pos] = arr[pos - 1];
            pos--;
            cmp = (*compare)(arr[pos - 1], temp);
        }
        arr[pos] = temp;
    }
}

// Returns the index of a key in the given array using binary search.
int binary_search(int key, const int arr[], int len, int (*compare)(int a, int b)) {
    int lo = 0, hi = len - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int cmp = (*compare)(key, arr[mid]);
        if (cmp < 0)
            hi = mid - 1;
        else if (cmp > 0)
            lo = mid + 1;
        else
            return mid;   // found at mid
    }
    return -1;            // not found
}

// Returns the index of a key in a given array using linear search.
int linear_search(int key, const int arr[], int len){
    for(int idx=0; idx<len; idx++)
        if(arr[idx] == key)
            return idx;
    return -1;
}

// Sorts the element of the given array using the selection sort algorithm.
void selection_sort(int arr[], int len, int (*compare)(int val1, int val2)){
    int x, y, min, temp;
    for (x=0; x<len-1; x++){
        min = x;
        for (y=x+1; y<len; y++)
            if ((*compare)(arr[y], arr[min]) < 0)
                min=y;

        temp=arr[x];
        arr[x]=arr[min];
        arr[min]=temp;
    }
}

// Returns the result of an ascending comparison.
int ascending(int a, int b) {
    return a - b;
}

// Returns the result of a descending comparison.
int descending(int a, int b) {
    return b - a;
}


