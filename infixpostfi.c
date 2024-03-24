#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAX 1000

typedef struct stack {
    char st[MAX];
    int top;
} stack;

stack s;
stack s2;
int Operand(char);
void create(stack *);
void push(stack *, char);
void pushe(stack *, int);
char pop(stack *);
int pope(stack *);
int isempty(stack *);
int isfull(stack *);
void eval(char []);
int icp(char);
int isp(char);
int main() {
    s.top = -1;
    char str[MAX];
    char post[MAX];
    int i = 0,a=0;
    printf("Enter the Infix Expression: ");
    fgets(str, sizeof(str), stdin);
    printf("The Postfix Expression is :");
    while (str[i] != '\0') {
        if (Operand(str[i])) {
            printf("%c", str[i]);
            post[a++]=str[i];
        } else if (str[i] == ')') {
            while (s.top >= 0 && s.st[s.top] != '(') {
            	 post[a++]=s.st[s.top];
                printf("%c", pop(&s));
                
                
            }
            if (s.st[s.top] == '(') {
                pop(&s);
            }
        } else {
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(') {
                while (!isempty(&s) && isp(s.st[s.top]) >= icp(str[i])) {
                	post[a++]=s.st[s.top];
                    printf("%c", pop(&s));
                    
                    
                }
                push(&s, str[i]);
            }
        }
        i++;
    }
    while (!isempty(&s)) {
    	   post[a++]=s.st[s.top];
        printf("%c", pop(&s));
    }
	printf("\n");
	
	eval(post);
    return 0;
}

int isfull(stack *s) {
    return (s->top == MAX - 1);
}

int isempty(stack *s) {
    return (s->top == -1);
}

int Operand(char s) {
    return (('A' <= s && s <= 'Z') || ('a' <= s && s <= 'z'));
}

void push(stack *s, char item) {
    if (isfull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->top++;
    s->st[s->top] = item;
}
void pushe(stack *s, int item) {
    if (isfull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->top++;
    s->st[s->top] = item;
}

char pop(stack *s) {
    if (isempty(s)) {
        printf("Stack Empty\n");
    }
    return(s->st[s->top--]);
}

int isp(char op) {
    if (op == '*' || op == '/') {
        return 3;
    } else if (op == '+' || op == '-') {
        return 2;
    } else if (op == '(') {
        return 1; 
    }
    return 0;
}

int icp(char op) {
    if (op == '*' || op == '/') {
        return 4;
    } else if (op == '+' || op == '-') {
        return 2;
    } else if (op == '(') {
        return 9;
    } else if (op == ')') {
        return 0;
    }
    return -1; 
}
int pope(stack *s) {
    if (isempty(s)) {
        printf("Stack Underflow\n");
        exit(1); 
    } else {
        return s->st[s->top--];
    }
}
void eval(char post[]){
    s2.top = -1;
    int operand;
    int i=0;
    while (post[i] != '\0') {
        if (Operand(post[i])) {
            printf("Enter the value of operand '%c': ", post[i]);
            scanf("%d", &operand);
            pushe(&s2, operand);
        } else if (post[i] != ' ' && post[i] != '\n') {
            int op2 = pope(&s2);
            int op1 = pope(&s2);
            

            switch (post[i]) {
                case '+':
                    pushe(&s2, op1 + op2);
                    break;
                case '-':
                    pushe(&s2, op1 - op2);
                    break;
                case '*':
                    pushe(&s2, op1 * op2);
                    break;
                case '/':
                    if (op2 == 0) {
                        printf("Division by zero\n");
                        exit(1); 
                    }
                    pushe(&s2, op1 / op2);
                    break;
                default:
                    printf("Invalid character in post expression\n");
                    exit(1); 
            }
        }
        i++;
    }   
    if (!isempty(&s2)) {
        printf("Result: %d\n", pope(&s2));
    } else {
        printf("Empty stack\n");
        exit(1); 
    }


}

