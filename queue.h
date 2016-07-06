#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H

struct node_q {
    void *data_q;
    struct node_q *next_q;
};

typedef struct node_q Node;
typedef Node *Node_P;

typedef struct {
    int size;
    Node_P front;
    Node_P rear;
} Queue;

Queue *queueCreate(void);

int queueIsEmpty(Queue *queue);

int enqueue(Queue *queue, void *data);

int dequeue(Queue *queue, void **data);

void queueDestroy(Queue *queue);

#endif //THREAD_QUEUE_H
