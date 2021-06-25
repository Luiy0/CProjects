/* employee_payroll.c
 * By Luis A. Flores (841102500)
 * 10/30/2015
 * This program displays the data of five different kind of employees.
*/

#include <stdio.h>

// Defines symbolic constants.
#define ID_SIZE 4
#define NAME_SIZE 20

// Defines enumeration type
typedef enum {HOURLY, SALES} EmployeeKind;

// Defines data structures.
typedef struct {
   float pay_rate, hours_worked;
} HourlyEmployee;

typedef struct {
   float commission_rate, sales_amount;
} SalesEmployee;

typedef struct {
   EmployeeKind kind;
   char employee_id[ID_SIZE + 1], full_name[NAME_SIZE + 1];
   union {
      HourlyEmployee hourly;
      SalesEmployee sales;
   };
} Employee;

// Declares functions using prototypes.
void show_data(const Employee *emp);
char *kind_str(EmployeeKind kind);
float salary(const Employee *emp);

// Starts the execution of the program.
int main(void){
    Employee arr[] = {
        {HOURLY, "1063", "Amelia Spencer", .hourly = {7.25, 60.0}},
        {SALES, "4497", "Rose Wellington", .sales = {8.00, 300.0}},
        {HOURLY, "7902", "Alex Spacestar", .hourly = {8.15, 39.0}},
        {SALES, "1685", "Michael Russo", .sales = {10.0, 250.37}},
        {HOURLY, "9033", "Dylan Jung", .hourly = {9.25, 53.0}}
    };

    printf("\t\t\t\tEmployee Payroll\n\n");
    printf("Kind\tId\tFull Name\t\tRate\tHours\\Sales\tWeekly Salary\n");
    printf("----\t--\t---------\t\t----\t-----------\t-------------\n");

    int arr_length = sizeof(arr) / sizeof(Employee);
    for (int idx = 0; idx < arr_length; idx++) {
        show_data(&arr[idx]);
        printf("\n");
    }
    printf("\nThank you.\n");
    return 0;
}

// Shows the data of a given employee.
void show_data(const Employee *emp) {
    printf("%s\t%s\t%s\t", kind_str(emp->kind), emp->employee_id, emp->full_name);
    switch (emp->kind) {
        case HOURLY:
            printf("\t%.2f/hr\t%.2f hrs\t$%.2f", emp->hourly.pay_rate, emp->hourly.hours_worked, salary(emp));
            break;
        case SALES:
            printf("\t%.2f %%\t$%.2f\t\t$%.2f", emp->sales.commission_rate, emp->sales.sales_amount, salary(emp));
            break;
    }
}

// Returns a string representation for the employee kind.
char *kind_str(EmployeeKind kind) {
    char *str[] = {"Hourly", "Sales"};
    return str[kind];
}

// Returns the salary of a given employee.
float salary(const Employee *emp) {
    switch (emp->kind) {
        case HOURLY:
            if(emp->hourly.hours_worked > 40)
                return (emp->hourly.pay_rate + 1.5) * emp->hourly.hours_worked;
            else
                return emp->hourly.pay_rate * emp->hourly.hours_worked;
            break;
        case SALES:
            return emp->sales.sales_amount * emp->sales.commission_rate;
            break;
    }
}
