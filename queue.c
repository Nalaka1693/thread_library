#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *queueCreate(void) {
	/*Allocate memory for a queue struct and return the reference*/

	Queue *queue = malloc(sizeof(Queue));
    queue -> size = 0;
	queue -> front = NULL;
	queue -> rear = NULL;

	return queue;
}

int queueIsEmpty(Queue *queue) {
	/*return 1 if queue is empty*/

	if (queue -> front == NULL) {
		return 1;
	}

	return 0;
}

int enqueue(Queue *queue, void *data) {
	/*Create a node and add data to it and link it to rear of the the queue*/

	Node_P node_p = malloc(sizeof(Node));

	if (node_p) {
		node_p -> data_q = data;
		node_p -> next_q = NULL;
        queue -> size++;

		if (queue -> front == NULL && queue -> rear == NULL) {
			queue -> front = node_p;
			queue -> rear = node_p;

			return 0;
		}

		(queue -> rear) -> next_q = node_p;
		queue -> rear = node_p;
	}

	return -1;
}

int dequeue(Queue *queue, void **data) {
	/*remove the queue's front node and get data in it*/

	if (!queueIsEmpty(queue)) {
		Node_P node_p = queue -> front;
        queue -> size--;
		
		*data = node_p -> data_q;
		queue -> front = node_p -> next_q;
		free(node_p);

		return 0;
	}

	*data = '\0';
	return -1;
}

void queueDestroy(Queue *queue) {
	/*destroy full queue by dequeuing and null its reference*/

	while (!queueIsEmpty(queue)) {
		void *c;
		dequeue(queue, &c);
	}

	free(queue);
	queue = NULL;
}

/*
int main() {
	Queue *queue1 = queueCreate();

    void *x = (void *) 'z';

	enqueue(queue1, x);
	enqueue(queue1, (void *) 'y');
    enqueue(queue1, (void *) 'c');
    enqueue(queue1, (void *) 'd');


	void *c;

	printf("\nPartially emptying\n");
	int i;
	for (i = 0; i < 3; ++i)	{
		dequeue(queue1, &c);
		printf("char = %ld\n", (long) c);
	}

	enqueue(queue1, (void *) 'e');
	enqueue(queue1, (void *) 'f');


	printf("\nFully emptying\n");
	while (!queueIsEmpty(queue1)) {
		dequeue(queue1, &c);
		printf("char = %ld\n", (long) c);
	}

	queueDestroy(queue1);
		
	return 0;	
}
*/