/* fibonacci_calc.c
 * Luis A. Flores (841102500)
 * 10/11/2015
 * This program calculates the nth term of the Fibonacci succession.
 */

#include <stdio.h>  // input-output

// Function prototypes
int fiboI(int term);  // Iterative version
int fiboR(int term);    // Recursive version

// Starts the execution of the program
int main(void){
    int term;   //holds the term entered by the user.
    printf("Enter a non negative integer: ");
    if(scanf("%d", &term) == 0){
        printf("Invalid input.\n");
        exit(0);
    }

    //Exists program if the entered term less than zero.
    if(term < 0){
        printf("Error! Negative number.\n");
        exit(0);
    }
    else{
       printf("The %d-nth term using iteration is %d\n",term,fiboI(term));
       printf("The %d-nth term using recursion is %d\n",term,fiboR(term));
    }

    printf("\nThank you.\n");
    return 0;
}

// Iterative version of the Fibonacci sequence
int fiboI(int term){

    if(term <= 1)
        return term;

    int first=1, second=1, third=0;
    for(int x=3; x<=term; x++){
        third = first+second;
        first=second;
        second=third;
        }
    return second;
    }

// Recursive version of the Fibonacci sequence
int fiboR(int term){
     if(term <= 1)
        return term;
     return fiboR(term - 1)+ fiboR(term - 2);
}


