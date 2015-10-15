/*
 * C program to implement stack. Stack is a LIFO data structure.
 * Stack operations: PUSH(insert operation), POP(Delete operation)
 * and Display stack.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
 
struct stack
{
    int stk[MAXSIZE];
    int top;
};
 
/*  Function to add an element to the stack */
void push (struct stack *s, int num)
{
    if (s->top == (MAXSIZE - 1))
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
        s->top = s->top + 1;
        s->stk[s->top] = num;
    }
    return;
}

/*  Function to delete an element from the stack */
int pop (struct stack *s)
{
    int num;
    if (s->top == - 1)
    {
        return (s->top);
    }
    else
    {
        num = s->stk[s->top];
        s->top = s->top - 1;
    }
    return(num);
}
/*  Function to display the status of the stack */
void display (struct stack *s)
{
    int i;
    if (s->top == 0)
    {
        printf ("Stack is empty\n");
        return;
    }
    else
    {
        printf ("\n The status of the stack is \n");
        for (i = s->top; i >= 0; i--)
        {
            printf ("%d\n", s->stk[i]);
        }
    }
    printf ("\n");
}

void main ()
{
	struct stack *history = (struct stack*)malloc(sizeof(struct stack));
    //push(history, 5);
    //push(history, 3);
    //push(history, 7);
    pop(history);
    display(history);
    
}
