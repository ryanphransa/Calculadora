#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//#include "equation.c"

enum {
    BUFFER_SIZE = 100
};

double parentheses[BUFFER_SIZE] = {0};
char variables[BUFFER_SIZE] = {0};

int pemdas(char operator) {
    switch (operator) {
        case '+': return 10;
        case '-': return 10;
        case '*': return 20;
        case '/': return 20;
        case '"': return 30;
        default:
            //printf("PEMDAS error: Not found a valid operator\n");
            return 0;
    }
}

double operation(double op1, double op2, char operator) {
    switch (operator) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        case '"':
            for (; op2 > 1; op2--) {
                op1 *= op1;
            }
            return op1;
        default:
            printf("Operation error: Not found a valid operator.\n");
            return 0;
    }
}

bool isoperator(char operator) {
    switch(operator) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '"':
            return true;
        default:
            return false;
    }
}

void fakegetline(char *operator, double *operand) {
    // indexes
    size_t i = 0, j = 0;
    int c;
    double n = 0, f = 10;
    bool float_point = false;

    bool variable_on = false;
    bool parentheses_on = false;
    int parentheses_nest = 0;

    while((c = getchar()) != EOF) {
        if (isdigit(c)) {
            if (!float_point)
                n = n * 10 + (c - '0');
            else {
                n = n + (c - '0') / f;
                f *= 10;
            }
        } else if (c == '.') {
            float_point = true;
        } else if (c == '(') {
            parentheses_on = true;
            parentheses_nest += 100;
        } else if (c == ')') {
            parentheses_nest -= 100;
            if (parentheses_nest < 100)
                parentheses_on = false;
        } else if (isoperator(c)) {
            if (parentheses_on)
                parentheses[j] = parentheses_nest;
            operand[i++] = n; 
            operator[j++] = c;

            float_point = false;
            n = 0, f = 10;
        } else if (isalpha(c)) {
            // variable
            variable_on = true;
            variables[i++] = c; // use the same index as operand
        } else if (c == '\n') {
            operand[i++] = n;
            break;
        } else {
            printf("ERROR\nThe format is wrong, breaking.\n");
            break;
        }
    }
    operand[i] = operator[i] = '\0';
}

void delete_operand(double *operand, size_t index) {
    for (; operand[index] != '\0'; index++) {
        operand[index] = operand[index+1];
    }
}

void delete_operator(char *operator, size_t index) {
    for (; operator[index] != '\0'; index++) {
        operator[index] = operator[index+1];
    }
}

void delete_parentheses(size_t index) {
    for (; parentheses[index] != '\0'; index++) {
        parentheses[index] = parentheses[index+1];
    }
}

double expression(char *operator, double *operand) {
    float results[BUFFER_SIZE];
    float result = 0;
    size_t my_op = 0;

    size_t ignore_it = 1; // cosmetic index '1)'

    for (size_t i = 0; ; i++) {
        if (pemdas(operator[i])+parentheses[i] > pemdas(operator[my_op])+parentheses[my_op]) {
            my_op = i;
        }

        if (operator[i] == '\0') {
            if (operator[my_op] == '\0')
                return operand[0];

            // below has cosmetic-print code
            printf("\t%d) ", ignore_it++);
            for (size_t k = 0; operand[k] != '\0'; k++) {
                printf("%.2f ", operand[k]);
                if (isoperator(operator[k])) {
                    if (parentheses[k] > 0)
                        printf("%cp ", operator[k]);
                    else
                        printf("%c ", operator[k]);
                }
            } putchar('\n');

            operand[my_op] = operation(operand[my_op], operand[my_op+1], operator[my_op]);

            delete_operand(operand, my_op+1);
            delete_operator(operator, my_op);
            delete_parentheses(my_op); // parentheses == operator, so we should delete the same element in both

            my_op = 0;
            i = 0;
        }
    }
}

int main() {
    printf(""
    "▙▗▌   ▞▀▖    ▜ ▞▀▖   ▜    \n"
    "▌▘▌▌ ▌▌ ▌▌  ▌▐ ▌  ▝▀▖▐ ▞▀▖\n"
    "▌ ▌▚▄▌▌ ▌▐▐▐ ▐ ▌ ▖▞▀▌▐ ▌ ▖\n"
    "▘ ▘▗▄▘▝▀  ▘▘  ▘▝▀ ▝▀▘ ▘▝▀ \n");

    char operator[BUFFER_SIZE];
    double operand[BUFFER_SIZE];

    while(1) {
        printf("Expression: ");
        fakegetline(operator, operand);
        
        double result = expression(operator, operand);

        printf("┌────────────────┐\n"
               "│  Result: %.2f  │\n"
               "└────────────────┘\n\n", result);
    }
    return 0;
}
