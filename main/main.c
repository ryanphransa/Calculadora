#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

enum {
    BUFFER_SIZE = 1000
};

char variables[BUFFER_SIZE] = {0};
bool two_members_operation = false;

float history[BUFFER_SIZE] = {0};
size_t b = 0; // for history;

size_t parentheses[BUFFER_SIZE] = {0};

char *fakegetline(char string[]) {
    int i, c;
    i = 0;
    while((c = getchar()) != '\n') {
        if (c != ' ')
            string[i++] = c;
    }
    string[i] = '\0';

    return string;
}

int isoperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' ) {
        return true;
    }
}

int pemdas(char operator) {
    switch (operator) {
        case '+': return 10;
        case '-': return 10;
        case '*': return 20;
        case '/': return 20;
        default:
            //printf("PEMDAS error: Not found a valid operator\n");
            return 0;
    }
}

float operation(float op1, float op2, char operator) {
    switch (operator) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        default:
            printf("Operation error: Not found a valid operator.\n");
            return 0;
    }
}

char invert_operator(char operator) {
    switch (operator) {
        case '+': return '-';
        case '-': return '+';
        case '*': return '/';
        case '/': return '*';
        default:
            printf("invert_operator error: Not found a valid operator.\n");
            return 0;
    }
}

float operation_order(char *operators, float *operands);

void convert(char string[], char *operators, float *operands) {
    size_t j = 0;
    size_t k = 0;

    float n = 0;
    float f = 10;

    bool float_point = false;
    two_members_operation = false;

    int sign = 1;
    bool parentheses_status = false;

    for (size_t i = 0; ; i++) {
        if (isdigit(string[i])) {
            if (!float_point)
                n = n * 10 + (string[i] - '0');
            else {
                n = n + (string[i] - '0') / f;
                f *= 10;
            }
        } else if (string[i] == '.') {
            float_point = true;
        } else if (string[i] == '-' && !isdigit(string[i-1])) {
            sign = -1;
        } else if (string[i] >= 'a' && string[i] <= 'z') {
            // variables
            n = string[i];
            variables[j] = string[i];
        } else if (string[i] == '=') {
            two_members_operation = true;
            string[i] = '+';
            --i;
        } else if (string[i] == '(') {
            parentheses_status = true;
        } else if (string[i] == ')') {
            parentheses_status = false;
        } else if (isoperator(string[i])) {
            if (parentheses_status)
                parentheses[k] = 1;
            if (!two_members_operation) {
                operators[k++] = string[i];
            } else {
                operators[k++] = /*invert_operator*/(string[i]);
            }
            operands[j++] = n * sign;
            
            float_point = false;
            f = 10;
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


float operation_order(char *operators, float *operands) {
    float results[BUFFER_SIZE] = {0};
    int my_op = 0;
    int last_op = 0;
    size_t t = 0;

    // This is the way i find to prioritize parentheses.
    int parentheses_priority = 100;
    for (size_t i = 1; ; i++) {
        /*if (parentheses[i] == 1 && parentheses[my_op] == 0) {
            if (pemdas(operators[i])+parentheses_priority > pemdas(operators[my_op])) {
                my_op = i;
            }
        } else if (parentheses[i] == 0 && parentheses[my_op] == 1) {
            if (pemdas(operators[i]) > pemdas(operators[my_op])+parentheses_priority) {
                my_op = i;
            }
        } else if (parentheses[i] == 1 && parentheses[my_op] == 1) {
            if (pemdas(operators[i])+parentheses_priority > pemdas(operators[my_op])+parentheses_priority) {
                my_op = i;
            }
        } else*/ if (pemdas(operators[i]) > pemdas(operators[my_op])) {
            my_op = i;
        }

        if (operators[i+1] == '\0' && operators[my_op] != 0) {
            // Break when every element of operators is == 'X'.
            if (operators[my_op] == 'X') {
                return results[last_op];
            }

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

            operators[my_op] = 'X';

            last_op = my_op;

            parentheses[my_op] = 0;

            i = my_op = 0;
        }
    }
}

int main() {
    char string[BUFFER_SIZE];

    float operands[BUFFER_SIZE];
    char operators[BUFFER_SIZE];

    while(1) { 
        fakegetline(string);

        // Convert string chars in operands and operators
        convert(string, operators, operands);

        // Start the operations calling with PEMDAS order
        float result = operation_order(operators, operands);
        history[b++] = result;

        if (!two_members_operation)
            printf("result is: %.4f\n", result);
        else
            printf("x is: %.4f\n", result);

        //clear arrays
        for (size_t i; i < 100; i++) {
            string[i] = 0;
            operands[i] = 0;
            operators[i] = 0;
        }
    }

    return 0;
}
