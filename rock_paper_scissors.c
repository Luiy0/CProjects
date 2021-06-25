/* rock_paper_scissors.c
 * Luis A. Flores (841102500)
 * 10/11/2015
 * This program is a simulation of the rock-paper-scissors game.
*/

#include <stdio.h>  // input-output
#include <stdlib.h> // srand, rand
#include <time.h>   // time

//Function prototypes
int userSel();                      // Prompts the user for a selection.
int winner(int comp, int user);     // Determines the winning case comparing the cpu and user values.
char replay();                      // Asks the user to play again.
void result(int count, int iter);   // Shows the percentage of wins.

// Starts the execution of the program.
int main(void){
    srand(time(NULL));      // Initializes random number generator with a time-derived seed.
    int cpu, user, value;   // variables for holding rdn number, user input and the winner.
    int iter=0, count=0;  // variables to calculate the average.
    char ans;                   // variable used for repetition.

    do{
        cpu = rand() %3;        // random value between three numbers
        user = userSel();

        if(user == -1)
            ans = replay();
        else{
            value = winner(cpu, user);
            ans = replay();

            if(value == 1)
                count++;
            if(value == 1 || value == -1)
                iter++;
        }//else

    }while(toupper(ans) == 'Y');
    result(count, iter);

    return 0;
} // main

// Prompts the user for a selection
int userSel(){
    int selection;
    printf("Enter your selection (0=Rock, 1=Paper, 2=Scissors): ");
    if(scanf("%d", &selection) == 0){
        printf("Invalid selection.\n\n");
        return -1;
    }
    else if(selection < 0 || selection > 2){
        printf("Invalid selection.\n\n");
        return -1;
    }
    else
        return selection;
}

// Determines the winning case comparing the cpu and user values
int winner(int comp, int user){
    switch(user){
    case 0: // user's rock case
        switch(comp){
        case 0: // cpu rock case
            printf("\nYour selection was %d(Rock) Vs. %d(Rock) It's a Tie!\n",user,comp);
            return 0;
            break;
        case 1: // cpu paper case
            printf("\nYour selection was %d(Rock) Vs. %d(Paper) You Lost!\n",user,comp);
            return -1;
            break;
        case 2: // cpu scissors case
            printf("\nYour selection was %d(Rock) Vs. %d(Scissors) You Won!\n",user,comp);
            return 1;
            break;
        }
        break;

    case 1: // user's paper case
         switch(comp){
        case 0: // cpu rock case
            printf("\nYour selection was %d(Paper) Vs. %d(Rock) You Won!\n",user,comp);
            return 1;
            break;
        case 1: // cpu paper case
            printf("\nYour selection was %d(Paper) Vs. %d(Paper) It's a Tie!\n",user,comp);
            return 0;
            break;
        case 2: // cpu scissors case
            printf("\nYour selection was %d(Paper) Vs. %d(Scissors) You Lost!\n",user,comp);
            return -1;
            break;
        }
        break;

    case 2: // user's scissors case
         switch(comp){
        case 0: // cpu rock case
            printf("\nYour selection was %d(Scissors) Vs. %d(Rock) You Lost!\n",user,comp);
            return -1;
            break;
        case 1: // cpu paper case
            printf("\nYour selection was %d(Scissors) Vs. %d(Paper) You Won!\n",user,comp);
            return 1;
            break;
        case 2: // cpu scissors case
            printf("\nYour selection was %d(Scissors) Vs. %d(Scissors) It't a Tie!\n",user,comp);
            return 0;
            break;
        }
        break;
    }//switch
}

// Shows the percentage of wins the user got
void result(int count, int iterations){
    float percentage = (count / (float)iterations)*100;
    printf("\nThe percentage of wins is: %.1f%%", percentage);
    printf("\nThank you for playing.\n");
}

// Prompts the user for replay
char replay(){
    char answer;    // holds the user's answer
    do{
        fflush(stdin); // clearing the input buffer
        printf("Do you wish to try again? (Y/N): ");
        scanf("%c",&answer);

        if(toupper(answer) != 'Y' && toupper(answer) != 'N')
            printf("Invalid answer.\n");

    }while(toupper(answer) != 'Y' && toupper(answer) != 'N');
    return answer;
}



