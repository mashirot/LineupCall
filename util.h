//
// Created by MashiroT on 2023/2/24.
//

#ifndef LINEUPCALL_UTIL_H
#define LINEUPCALL_UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
int isValidPhoneNumber(char* phoneNumber);
void inform(char* phoneNum, char* tableType, int tableId);
int isValidDateRange(char* files, int start, int end);
#endif //LINEUPCALL_UTIL_H
