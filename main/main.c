#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP   100
#define NUMBER  '0'
#define MAXVAL 100

static int getop(char []);
static void push(double);
static double pop(void);

int sp = 0;      
int spInt = 0;
double val[MAXVAL];

void printWelcome(void) {
    const int sz = 255;

    char str[sz];
    FILE *fp;

    fp = fopen("welcm.txt", "r");

    while (fgets(str,sz,fp)!=NULL) {
        printf("%s", str);
    };

    fclose(fp);
}

int main(void)
{
    printWelcome();

    int type;
    double op1;
    double op2;
    int op1_int;
    int op2_int;
    char s[MAXOP];
    double result;
    double op;
    char operator;
    
    bool nonl = false; // no newline, doesn't call and print pop() in '\n'

    while((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case '=':
                result = pop();
                switch(operator) {
                    case '*':
                        push(result / op);
                        break;
                    case '+':
                        push(result - op);
                        break;
                    case '-':
                        push(result + op);
                        break;
                    case '/':
                        push(result * op);
                        break;
                }
                break;
            case '-':
                op2 = pop();
                op1 = pop();
                operator = '-';
                if (op1 == 'x') {
                    op = op2;
                    break;
                }
                else if (op2 == 'x') {
                    op = op1;
                    break;
                }
                push(op1 - op2);
                break;
            case '+':
                op2 = pop();
                op1 = pop();
                operator = '+';
                if (op1 == 'x') {
                    op = op2;
                    break;
                }
                else if (op2 == 'x') {
                    op = op1;
                    break;
                }
                push(op1 + op2);
                break;
            case '*':
                op2 = pop();
                op1 = pop();
                operator = '*';
                if (op1 == 'x') {
                    op = op2;
                    break;
                }
                else if (op2 == 'x') {
                    op = op1;
                    break;
                }
                push(pop() * pop());
                break;
            case 'z':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                op1 = pop();
                operator = '/';
                if (op1 == 'x' && op2 != 0.0) {
                    op = op2;
                    break;
                }
                else if (op2 == 'x') {
                    op = op1;
                    break;
                }

                if(op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2_int = pop();
                op1_int = pop();
                push(op1_int % op2_int);
                break;
            case '\n':
                if(nonl == false)
                    printf("\t%.8g\n", pop());
                nonl = false;
                break;
            case 'p': // print stack
                if (sp > 0) {
                    printf("stack: ");
                    for(int i = 0; i < sp; i++)
                        printf("%d ", val[i]);
                    nonl = true;
                }
                else
                    printf("error: can't print stack, stack empty");
                putchar('\n');
                break;
            case 'r': // replicate last stack element
                if (sp > 0) 
                    push(val[sp]);
                else
                    printf("error: can't replicate, stack empty");
                break;
            case 's': // swap last two stack elements
                if (sp > 1) {
                    int temp = val[sp-1];
                    val[sp-1] = val[sp-2];
                    val[sp-2] = temp;

                    printf("last two stack elements swapped succesfully\n");

                    nonl = true;
                }
                else
                    printf("error: not enough elements to swap\n");
                break;
            case 'c': // clear stack
                while (sp > 0)
                    pop();
                nonl = true;
                break;
            case 'x':
                push('x');
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

static void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

static double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

static int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

static void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

static int getop(char s[])
{
    int i, c, sign;

    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    sign = 1;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c*sign;

    i = 0;
    if (c == '-') { 
        sign = -1;
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER; 
}
