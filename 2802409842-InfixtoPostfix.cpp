#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//infix to postfix using stack

struct Stack
{
    char arr[MAX];
    int top;
};


void init(Stack *s) 
{
    s->top = -1;
}


int isEmpty(Stack *s) 
{
    return s->top == -1;
}


int isFull(Stack *s) 
{
    return s->top == MAX - 1;
}

void push(Stack *s, char c) 
{
    if (isFull(s)) 
	{
        printf("Stack overflow\n");
        return;
    }
    s->arr[++s->top] = c;
}


char pop(Stack *s) 
{
    if (isEmpty(s)) 
	{
        printf("Stack underflow\n");
        return -1;
    }
    return s->arr[s->top--];
}


int precedence(char op) 
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


void infixToPostfix(char *infix, char *postfix) 
{
    Stack s;
    init(&s);
    int i = 0, j = 0;
    char token;
    
    while ((token = infix[i++]) != '\0') 
    {
        if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token >= '0' && token <= '9')) 
		{
            postfix[j++] = token;
        } 
		else if (token == '(') 
		{
            push(&s, token);
        } 
		else if (token == ')') 
		{
            while (!isEmpty(&s) && s.arr[s.top] != '(') 
			{
                postfix[j++] = pop(&s);
            }
            pop(&s); 
        } 
		else 
		{
            while (!isEmpty(&s) && precedence(s.arr[s.top]) >= precedence(token)) 
			{
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }
    
    while (!isEmpty(&s)) 
	{
        postfix[j++] = pop(&s);
    }
    
    postfix[j] = '\0';
}


int main() 
{
    char infix[MAX], postfix[MAX];
    printf("Enter infix: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    
    return 0;
}

