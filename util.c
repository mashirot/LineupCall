//
// Created by MashiroT on 2023/2/24.
//

#include "util.h"
#include "strptime.c"

void inform(char *phoneNum, char *tableType, int tableId) {
    printf("���Ͳ�֪ͨ���װ��� %s, �õ���, �����Ͳ�, ����: %s, ����: %d\n", phoneNum + 7, tableType, tableId);
}

int isValidPhoneNumber(char *phoneNumber) {
    int length = strlen(phoneNumber);
    if (length != 11) {
        return 0;
    }
    for (int i = 0; i < length; i++) {
        if (!isdigit(phoneNumber[i])) {
            return 0;
        }
    }
    long long prefix = _atoi64(phoneNumber);
    if (prefix == 0 || (prefix < 13000000000ll || prefix > 19999999999ll)) {
        return 0;
    }
    return 1;
}

int isValidDateRange(char *files, int start, int end) {
    struct tm tempPrev;
    strptime(&files[start], "%Y-%m-%d 00:00:00", &tempPrev);
    time_t prev = mktime(&tempPrev);
    for (int i = start + 1; i < end; i++) {
        struct tm tempCurr;
        strptime(&files[i], "%Y-%m-%d 00:00:00", &tempCurr);
        time_t curr = mktime(&tempCurr);
        if (difftime(prev, curr) != 24 * 60 * 60) {
            return 0;
        }
        prev = curr;
    }
    return 1;
}