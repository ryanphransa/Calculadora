#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_VAL 100

int PEMDAS(char operator) {
    switch(operator) {
        case '+':
            return 10;
        case '-':
            return 10;
        case '*':
            return 20;
        case '/':
            return 20;
        default:
            return 0;
    }
}

int operation(int x, int y, char op) {
    switch(op) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        default:
            printf("error: operator don't identified\n");
            return 0;
    }
}

int isoperator(char c) {
    static char operator = 0;
    if (c == '+' || c == '-' ||
        c == '*' || c == '/') {
        operator = c;
        return true;
    }
    else 
        return operator;
}

void start(char s[]) {
    int i = 0;
    int j = 0;
    int k = 0;

    int result = 0;

    printf("%s\n", s);
    int operand[MAX_VAL];
    int operator[MAX_VAL];

    int prior, prior_index;

    int n = 0;

    while (s[i] != '\0') {
        // This search can't be increasing, need to apply PEMDAS order
        // of operations.
        /*for (i = prior = prior_index = 0; i < strlen(s); i++) {
            if (isoperator(s[i]) == true && PEMDAS(s[i]) > prior) {
                prior = PEMDAS(s[i]); 
                prior_index = i;
            }
        }*/
        //printf("we should start with: s[i] = %c\n", s[prior_index]);


        if (isdigit(s[i]))
        {
            operand[j] = s[i] - '0';
            if (isoperator(operator[0]) == true && result == 0)
            {
                result = operation(operand[j-1], operand[j], operator[k-1]); 
                printf("result -> %d\n", result); 
                printf("x = %d, y = %d\n", operand[j-1], operand[j]);
            }
            else if (isoperator(operator[0]) && result > 0 || result < 0)
            {
                result = operation(result, operand[j], operator[k-1]);
                printf("result -> %d\n", result);
            }
            ++j;
        }
        else if (isoperator(s[i]) == true)
        {
            operator[k++] = s[i];
        }
        else if (s[i] == '(' || s[i] == ')') {
            
        }

        printf("%c = s[i], %d = j\n",s[i], j);
        ++i;
    }
}

char *fakegetline(char s[]) {
    int i, c;
    i = 0;
    while((c = getchar()) != '\n')
    {
        if (c != ' ')
            s[i++] = c;
    }
    s[i] = '\0';

    return s;
}

int main() {
    char s[MAX_VAL];
    start(fakegetline(s));

    return 0;
}
