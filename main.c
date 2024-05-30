#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXIMUM_QUEUE_ELEMENTS 3

typedef struct SequentialCircularQueue {
    int beginning;
    int end;
    int data[MAXIMUM_QUEUE_ELEMENTS];
} SequentialCircularQueue;

SequentialCircularQueue *createSequentialCircularQueue();

bool isQueuePointerNull(SequentialCircularQueue *queue);

void queue(SequentialCircularQueue *queue, int data);

int dequeue(SequentialCircularQueue *queue);

int peek(SequentialCircularQueue *queue);

SequentialCircularQueue *createSequentialCircularQueue() {
    SequentialCircularQueue *newQueue = (SequentialCircularQueue *) malloc(sizeof(SequentialCircularQueue));
    if (newQueue == NULL) {
        printf("Failed to allocate memory in createSequentialCircularQueue().\n");
        exit(EXIT_FAILURE);
    }
    newQueue->beginning = -1;
    newQueue->end = -1;
    return newQueue;
}

bool isQueuePointerNull(SequentialCircularQueue *queue) {
    if (queue == NULL) {
        printf("Queue pointer is null.\n");
        return true;
    }
    return false;
}

void queue(SequentialCircularQueue *queue, int data) {
    if (isQueuePointerNull(queue)) {
        return;
    }
    if ((queue->beginning == queue->end + 1) || (queue->beginning == 0 && queue->end == MAXIMUM_QUEUE_ELEMENTS - 1)) {
        printf("Queue is full.\n");
        return;
    }
    if (queue->beginning == -1) {
        queue->beginning = 0;
    }
    queue->end++;
    if (queue->end >= MAXIMUM_QUEUE_ELEMENTS) {
        queue->end = 0;
    }
    queue->data[queue->end] = data;
    printf("%d queued.\n", data);
}

int dequeue(SequentialCircularQueue *queue) {
    if (isQueuePointerNull(queue)) {
        return INT_MIN;
    }
    if (queue->beginning == -1) {
        printf("Queue is empty.\n");
        return INT_MIN;
    }

    int dequeuedData = queue->data[queue->beginning];

    if (queue->beginning == MAXIMUM_QUEUE_ELEMENTS - 1) {
        queue->beginning = 0;
    } else {
        queue->beginning++;
    }
    if ((queue->beginning == queue->end + 1) || (queue->beginning == 0 && queue->end == MAXIMUM_QUEUE_ELEMENTS - 1)) {
        queue->beginning = -1;
        queue->end = -1;
    }
    return dequeuedData;
}

int peek(SequentialCircularQueue *queue) {
    if (isQueuePointerNull(queue)) {
        return INT_MIN;
    }
    if (queue->beginning == -1) {
        printf("Queue is empty.\n");
        return INT_MIN;
    }
    return queue->data[queue->beginning];
}

int main(void) {
    SequentialCircularQueue *testQueue = createSequentialCircularQueue();

    for (int i = 0; i < MAXIMUM_QUEUE_ELEMENTS + 1; i++) {
        queue(testQueue, i * 11);
    }
    for (int i = 0; i < MAXIMUM_QUEUE_ELEMENTS + 1; i++) {
        printf("%d dequeued.\n", dequeue(testQueue));
    }
    queue(testQueue, 255);
    printf("%d peeked.\n", peek(testQueue));;
    for (int i = 0; i < MAXIMUM_QUEUE_ELEMENTS + 1; i++) {
        queue(testQueue, i * 11);
    }
    free(testQueue);
    return 0;
}
