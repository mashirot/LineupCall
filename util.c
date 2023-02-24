//
// Created by MashiroT on 2023/2/24.
//

#include "util.h"

void inform(char* phoneNum, char* tableType, int tableId) {
    printf("【就餐通知】亲爱的 %s, 久等了, 请进店就餐, 桌型: %s, 桌号: %d\n", phoneNum + 7, tableType, tableId);
}

int isValidPhoneNumber(char* phoneNumber) {
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