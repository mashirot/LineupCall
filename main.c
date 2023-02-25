#include <stdio.h>
#include <pthread.h>
#include "manu.h"
#include "data.h"
#include "file.h"

extern Queue SMALL_TABLE_QUEUE;
extern Queue MID_TABLE_QUEUE;
extern Queue LARGE_TABLE_QUEUE;
extern Queue SMALL_TABLE_USER_QUEUE;
extern Queue MID_TABLE_USER_QUEUE;
extern Queue LARGE_TABLE_USER_QUEUE;
extern int enterNum;
extern int totalNum;
extern int smallTableNum;
extern int midTableNum;
extern int largeTableNum;
extern int smallTableEnterNum;
extern int midTableEnterNum;
extern int largeTableEnterNum;
pthread_t thread;

int main() {
    initQueue(&SMALL_TABLE_QUEUE);
    initQueue(&MID_TABLE_QUEUE);
    initQueue(&LARGE_TABLE_QUEUE);
    initQueue(&SMALL_TABLE_USER_QUEUE);
    initQueue(&MID_TABLE_USER_QUEUE);
    initQueue(&LARGE_TABLE_USER_QUEUE);
    if (pthread_create(&thread, NULL, timer_thread, NULL)) {
        fprintf(stderr, "线程创建失败\n");
        return 0;
    }
    homePage();
    if (pthread_detach(thread)) {
        fprintf(stderr, "线程结束失败\n");
    }
    return 0;
}
