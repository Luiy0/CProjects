/* diving_competition.c
 * By Luis A. Flores (841102500)
 * 10/30/2015
 * This program reads a file with the data of a diving competition and displays the results.
 * The program also creates a file with a copy of the report.
*/

#include <stdio.h>  //File
#include <stddef.h> //for NULL
#include <stdlib.h> //for exit

// Defines symbolic constants
#define ID_SIZE 4
#define NAME_SIZE 10
#define NUM_SCORES 10

// Defines the diver data structure
typedef struct {
   char diver_id[ID_SIZE + 1],
        first_name[NAME_SIZE + 1],
        last_name[NAME_SIZE + 1];
   float scores[NUM_SCORES];
} Diver;

// Declares functions using prototypes
Diver read_data(FILE *in);
float trunc_average(const Diver *div, float *arr, int count);
void write_results(FILE *out, const Diver *div, float *arr, int count);
void show_data(const Diver *div, float *arr, int count);

// Starts the execution of the program
int main(void){
    FILE *competition_file = fopen("competition.txt", "r");
    if (competition_file == NULL){
        fprintf(stderr, "Error: File competition.txt was not found.\n");
        exit(1);
    }

    FILE *report_file = fopen("report.txt", "w");
    Diver div = read_data(competition_file);

    float arr[10];
    int count = 0;

    printf("\t\tDiving Competition Results\n\n");
    printf("Id\tName\t\t\t\tTrunc. Average\n");
    printf("--\t----\t\t\t\t--------------\n");

    fprintf(report_file,"\t\tDiving Competition Results\n\n");
    fprintf(report_file,"Id\t\tName\t\t\tTrunc. Average\n");
    fprintf(report_file,"--\t\t----\t\t\t--------------\n");

    while (!feof(competition_file)){
        write_results(report_file, &div, arr, count);
        count++;
        show_data(&div, arr, count);
        div = read_data(competition_file);
    }

    winner(arr, count, &div);
    fclose(competition_file);
    fclose(report_file);
    fprintf(stdout, "\n\nFiles have been processed.\n");
    return 0;
}

// Reads and returns the data of a diver
Diver read_data(FILE *in){
    Diver div;
    fscanf(in, "%s %s %s", div.diver_id, div.first_name, div.last_name);
    for (int idx = 0; idx < NUM_SCORES; idx++)
        fscanf(in, "%f", &div.scores[idx]);
    return div;
}

// Returns the truncated average of a given diver
float trunc_average(const Diver *div, float *arr, int count){
    float sum = 0;
    float min = div->scores[0];
    float max = div->scores[0];
    int idxmax = 0, idxmin = 0;

    // Min score
    for(int x = 0; x < NUM_SCORES; x++)
        if(div->scores[x] < min){
            min = div->scores[x];
            idxmin = x;
        }
    // Max score
    for(int y = 0; y < NUM_SCORES; y++)
        if(div->scores[y] > max){
            max = div->scores[y];
            idxmax = y;
        }
    // Discarding max and min scores
    for(int idx = 0; idx < NUM_SCORES; idx++)
        if(idx != idxmax && idx != idxmin)
            sum += div->scores[idx];

    arr[count] = (float)sum / (NUM_SCORES-2);
    return (float)sum / (NUM_SCORES-2);
}

// Writes the data and average of a given diver
void write_results(FILE *out, const Diver *div, float *arr, int count){
    if(my_strlen(div->first_name) + my_strlen(div->last_name) > 8)
        fprintf(out, "%s\t%s, %s\t\t\t%.3f\n", div->diver_id, div->first_name, div->last_name, trunc_average(div, arr, count));
    else
        fprintf(out, "%s\t%s, %s\t\t\t\t%.3f\n", div->diver_id, div->first_name, div->last_name, trunc_average(div, arr, count));
}

void show_data(const Diver *div, float *arr, int count){
    printf("%s\t%s, %s\t\t\t\t%.3f\n", div->diver_id, div->first_name, div->last_name, trunc_average(div, arr, count));
}

// Determines the winner
void winner(float *arr, int count, const Diver *div){
    float max = *arr;
    for(int x = 0; x <= count; x++)
        if(arr[x] > max)
            max = arr[x];
    printf("\nThe winner scored %.3f", max);
    // A cual diver me estaré refiriendo?
    // Otro array para guardar los nombres? bidimensional?
}

//Determines the length of a string
int my_strlen(const char *str){
    int count = 0;
    char *ptr = str;
    while (*ptr++ != '\0');
    return ptr - str - 1;;
}







