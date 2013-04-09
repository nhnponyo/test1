#include <stdio.h>
#include <stdlib.h>

#define MAX_Q_SIZE 7
typedef int element;
typedef struct {
	element queue[MAX_Q_SIZE];
	int front;
	int rear;
} queue_t;

void init(queue_t *q);
void enqueue(queue_t *q, element item);
element dequeue(queue_t *q);
int isEmpty(queue_t *q);
int isFull(queue_t *q);
void queueFull(queue_t *q);

int main()
{
	queue_t q;
	init(&q);
	enqueue(&q,1);
	enqueue(&q,2);
	enqueue(&q,3);
	enqueue(&q,4);
	enqueue(&q,5);
	enqueue(&q,6);
	printf("is full? %d\n", isFull(&q));
	printf("dequeue %d\n", dequeue(&q));
	printf("is full? %d\n", isFull(&q));
	enqueue(&q,7);
	printf("is full? %d\n", isFull(&q));
	printf("dequeue %d\n", dequeue(&q));
	printf("dequeue %d\n", dequeue(&q));
	printf("dequeue %d\n", dequeue(&q));
	printf("dequeue %d\n", dequeue(&q));
	printf("dequeue %d\n", dequeue(&q));
	printf("dequeue %d\n", dequeue(&q));
	printf("dequeue %d\n", dequeue(&q));
	printf("never reach this code\n");

	return 0;
}

void init(queue_t *q)
{
	q->front = q-> rear =0;
}

int isFull(queue_t *q)
{
	return (q->front == ( (q->rear+1) % MAX_Q_SIZE));
}

int isEmpty(queue_t *q)
{
	//implement 
}

void enqueue(queue_t *q, element item)
{
	if(isFull(q))
		queueFull(q);

	q->rear= (q->rear+1)% MAX_Q_SIZE;
	q->queue[q->rear] = item;
}

void queueFull(queue_t *q)
{
	fprintf(stderr,"queue full error\n");
	exit(EXIT_FAILURE);
}

element dequeue(queue_t *q)
{
	element item;
	//implement 
	return item;
}
