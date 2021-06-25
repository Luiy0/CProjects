/* array_stats.c
 * Luis A. Flores (841102500)
 * 10/11/2015
 * This program calculates the minimum, average and the odd numbers in an array.
 */

#include<stdio.h> // input-output
#define LEN 10

// Function prototypes
float average(const int *arr, int len);     //calculates the average given an array of integers
int minimum(const int *arr, int len);     //determines the minimum number given an array of integers
int oddCount(const int arr[], int len);    //determines how many odd numbers are in a given array of integers
void results(float ave, int min, int odd); //output results

// Starts execution of the program
int main(void){
    int arr[LEN];
    printf("Enter the 10 elements: ");
    for(int idx=0; idx<LEN; idx++)
        if(scanf("%d", arr+idx) == 0){
            printf("Input error.\n");
            exit(0);
        }

    float ave = average(arr, LEN);
    int min = minimum(arr, LEN);
    int odd = oddCount(arr, LEN);
    results(ave, min, odd);

    return 0;
}

// Calculates the average given 10 random numbers
float average(const int *arr, int len){
    float acum = 0;
    for(int idx=0; idx<len; idx++)
        acum += *(arr+idx);
    return acum/10.0;
}

// Finds the minimum of 10 random numbers
int minimum(const int *arr, int len){
    int min = *arr;
    for(int idx=1; idx<len; idx++)
        if(min > *(arr+idx))
            min = *(arr+idx);
    return min;
}

// Counts the odd numbers in the array
int oddCount(const int arr[], int len){
    int count=0;
    for(int idx=0; idx<len; idx++)
        if(!(arr[idx]%2 == 0))
            count++;
    return count;
}

// Shows the results
void results(float ave, int min, int odd){
    printf("\nThe minimum element is: %d\n",min);
    printf("The average of the elements is: %.1f%\n",ave);
    printf("There are %d odd elements\n",odd);
    printf("\nThank you for using the program!\n");
}
