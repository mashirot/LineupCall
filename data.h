//
// Created by MashiroT on 2023/2/24.
//

#ifndef LINEUPCALL_DATA_H
#define LINEUPCALL_DATA_H

#include <malloc.h>
#include <memory.h>
#include <time.h>

typedef struct {
    int id;
} Table;
typedef struct {
    int type;
    char* phoneNumber;
    int memNum;
} Customer;

typedef struct {
    void* val;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} Queue;

typedef struct {
    int enterNum;
    int totalNum;
    int smallTableNum;
    int midTableNum;
    int largeTableNum;
    int smallTableEnterNum;
    int midTableEnterNum;
    int largeTableEnterNum;
} Data;

void offer(Queue* queue, void* data, size_t dataSize);
void* peekLast(Queue* queue);
void* poll(Queue* queue);
void initQueue(Queue* queue);

void resetStatisticalData();

#define SMALL_TABLE 1
#define MID_TABLE 2
#define LARGE_TABLE 3
#define SMALL_TABLE_CAPACITY 2
#define MID_TABLE_CAPACITY 4
#define LARGE_TABLE_CAPACITY 12

#endif //LINEUPCALL_DATA_H
