#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 4

typedef int element;

typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} stack_t;

void init(stack_t * s);
int is_empty(stack_t *s);
int is_full(stack_t *s);
void push(stack_t *s, element item);
element pop(stack_t *s);
element peek(stack_t *s);
void stack_full(stack_t *s);

int main()
{
	int b;
	stack_t stack;
	init(&stack);
	b = is_empty(&stack);
	printf("after init, stack empty? %d\n", b);
	push(&stack,1);
	b = is_empty(&stack);
	printf("after push, stack empty? %d\n", b);
	push(&stack,2);
	push(&stack,5);
	push(&stack,10);
	b = is_full(&stack);
	printf("after 4 push, stack full? %d\n", b);
	element x = pop(&stack);
	printf("pop element= %d\n", x);
	push(&stack,10);
	push(&stack,10);
	printf("never reach this code\n");
	return 0;
}


void init(stack_t* s)
{
	s->top = -1;
}

int is_empty(stack_t* s)
{
	return (s->top==-1);
}

int is_full(stack_t* s)
{
	//implement
}

void push(stack_t *s, element item)
{
	if(is_full(s))
		stack_full(s);
	s->top++;
	s->stack[s->top] = item;
}
element pop(stack_t *s)
{
	//implement
}

void stack_full(stack_t *s)
{
	//implement
}
