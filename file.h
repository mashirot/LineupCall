//
// Created by MashiroT on 2023/2/24.
//

#ifndef LINEUPCALL_FILE_H
#define LINEUPCALL_FILE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include "data.h"

void output();
void *timer_thread();
Data deserialize(char* filename);
#endif //LINEUPCALL_FILE_H
