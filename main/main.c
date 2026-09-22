#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

char *fakegetline(char string[]) {
    int i, c;
    i = 0;
    while((c = getchar()) != '\n') {
        if (c != ' ')
        string[i++] = c;
        if (c == EOF) {
            printf("FEIJAO\n");
        }
    }
    string[i] = '\0';

    return string;
}

int isoperator(char c) {
    static char operator = 0;
    if (c == '+' || c == '-' ||
        c == '*' || c == '/' ) {
        operator = c;
        return true;
    }
    else
        return operator;
}

int pemdas(char operator) {
    switch (operator) {
        case '+':
            return 10;
        case '-':
            return 10;
        case '*':
            return 20;
        case '/':
            return 20;
        case '(':
            return 30;
        case ')':
            return 30;
        default:
            return 0;
    }
}

float operation(float op1, float op2, char operator) {
    switch (operator) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
    }
}

void convert(char string[], char *operators, float *operands) {
    for (size_t i = 0; ; i++) {
        static size_t j = 0;
        static size_t k = 0;
        static float n = 0;

        static int sign = 1;

        if (isdigit(string[i])) {
            n = n * 10 + (string[i] - '0');
        } else if (string[i] == '.') {
            // do something bro 
        } else if (string[i] == '-' && !isdigit(string[i-1])) {
            sign = -1;
        } else if (isoperator(string[i])) {
            operators[k++] = string[i];
            if (n > 0) {
                operands[j++] = n * sign;
            }
            n = 0;
            sign = 1;
        }

        if (string[i] == '\0') {
            operands[j] = '\0';
            operators[k] = '\0';

            operands[j++] = n * sign;
            n = 0;
            sign = 1;
            break;
        }
    }
}


// Instead of global operators, pointers to the first element;
float operation_order(char *operators, float *operands) {
    float results[100] = {0};
    for (size_t i = 1; ; i++) {
        printf("a");
        static int my_op = 0;
        static int last_op = 0;

        if (pemdas(operators[i]) > pemdas(operators[my_op])) {
            my_op = i;
        }

        if (operators[i] == '\0' && operators[my_op] != 0) {
            // Break when every element of operators is == 'X'.
            if (operators[my_op] == 'X') {
                return results[last_op];
            }

            printf("%c <- operator im using\n"
                   "%d <- last_op\n", operators[my_op], last_op);

            if (results[last_op] == 0) {
                results[my_op] = operation(operands[my_op],
                                           operands[my_op+1],
                                           operators[my_op]);
            } else if (operators[my_op-1] == 'X' &&
                       operators[my_op+1] == 'X') {
                results[my_op] = operation(results[my_op-1],
                                           results[my_op+1],
                                           operators[my_op]);
            } else if (last_op < my_op) {
                if (last_op != my_op-1 && operators[my_op-1] != 'X') {
                    results[my_op] = operation(operands[my_op],
                                               operands[my_op+1],
                                               operators[my_op]);
                }
                else {
                    results[my_op] = operation(results[last_op],
                                               operands[my_op+1],
                                               operators[my_op]);
                }
            } else if (last_op > my_op) {
                if (last_op != my_op+1 && operators[my_op+1] != 'X') {
                    results[my_op] = operation(operands[my_op],
                                               operands[my_op+1],
                                               operators[my_op]);
                }
                else {
                    results[my_op] = operation(results[last_op],
                                               operands[my_op], 
                                               operators[my_op]); 
                }
            }

            printf("%f <- result\n", results[my_op]);
            
            // delete operator element that was already used.
            operators[my_op] = 'X';

            // last_op is being used to identify the location of the
            // last operator used in a operation.
            last_op = my_op;

            i = my_op = 0;
        }
    }

    printf("Operands: \n");
    for(size_t i = 0; operands[i] != 0; i++)
        printf("%f ", operands[i]);

    putchar('\n');

    printf("Operators: \n");
    for(size_t i = 0; operators[i] != 0; i++) {
        printf("%c ", operators[i]);
    }

    printf("Results: \n");
    for(size_t i = 0; operators[i] != 0; i++) {
        printf("%f ", results[i]);
    }
}

int main() {
    char string[100];

    float operands[100];
    char operators[100];
    while(1) { 
        fakegetline(string);

        // Convert string chars in operands and operators
        convert(string, operators, operands);

        // Start the operations calling with PEMDAS order
        float result = operation_order(operators, operands);

        printf("result is: %f\n", result);

        //clear arrays
        for (size_t i; i < 100; i++) {
            string[i] = 0;
            operands[i] = 0;
            operators[i] = 0;
        }
    }

    return 0;
}
