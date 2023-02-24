//
// Created by MashiroT on 2023/2/24.
//

#include "data.h"
Queue SMALL_TABLE_QUEUE;
Queue MID_TABLE_QUEUE;
Queue LARGE_TABLE_QUEUE;
Queue SMALL_TABLE_USER_QUEUE;
Queue MID_TABLE_USER_QUEUE;
Queue LARGE_TABLE_USER_QUEUE;
int enterNum = 0;
int totalNum = 0;
int smallTableNum = 0;
int midTableNum = 0;
int largeTableNum = 0;
int smallTableEnterNum = 0;
int midTableEnterNum = 0;
int largeTableEnterNum = 0;
time_t startTime;

void offer(Queue* queue, void* data, size_t dataSize) {
    Node* node = malloc(sizeof(Node));
    node->val = malloc(dataSize);
    memcpy(node->val, data, dataSize);
    node->next = NULL;
    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
}
void* peekLast(Queue* queue) {
    return queue->tail->val;
}
void* poll(Queue* queue) {
    Node* temp = queue->head;
    void* data = temp->val;
    queue->head = queue->head->next;
    queue->size--;
    free(temp);
    return data;
}

void initQueue(Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

void resetStatisticalData() {
    enterNum = 0;
    totalNum = 0;
    smallTableNum = 0;
    midTableNum = 0;
    largeTableNum = 0;
    smallTableEnterNum = 0;
    midTableEnterNum = 0;
    largeTableEnterNum = 0;
}