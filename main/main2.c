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
        // PEMDAS logic
        // r(1, 2, 3...) = results of the order of operations
        // 
        // r1 means the first operation to be done, in this case
        // is the operation of the base 3 with expoent 2 (3 * 3).
        //
        // 1 + 2 * 3 / 3"2
        // 1 + 2 * 3 / (3*3)    => r1=(3*3)
        // 1 + (2 * 3) / (3*3)  => r1=(3*3), r2=(2*3)
        // 1 + ((2*3) / (3*3))  => r1=(3*3), r2=(2*3), r3=r1/r2
        // (1 + ((2*3) / (3*3)) => r1=(3*3), r2=(2*3), r3=r1/r2, r4= 1+r3

        static int op_pemdas = 0;
        static int op_location = 0;

        if (isoperator(s[i]) && PEMDAS(s[i]) > op_pemdas) {
            op_pemdas = PEMDAS(s[i]);
            op_location = i;
        }

        int results[100];
        static int r = 0;

        if (op_location > 0) {
            results[r] = operation(s[op_location-1]-'0', s[op_location+1]-'0', s[op_location]);
            printf("op1:%d op2:%d operator:%c\n", s[op_location-1]-'0', s[op_location+1]-'0', s[op_location]);
            printf("result:%d\n", results[r++]);
        }
        ++i;
    }
}

char *fakegetline(char s[]) {
    int i, c;
    i = 0;
    while((c = getchar()) != '\n') {
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
