//
// Created by MashiroT on 2023/2/24.
//

#include "manage.h"
#include "data.h"
#include "util.h"
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

void takeTable(int tableType) {
    switch (tableType) {
        case SMALL_TABLE: {
            if (SMALL_TABLE_USER_QUEUE.size == 0 || SMALL_TABLE_QUEUE.size >= 10) {
                break;
            }
            Customer sCustomer = *(Customer *) poll(&SMALL_TABLE_USER_QUEUE);
            int sId = generateId(SMALL_TABLE, &SMALL_TABLE_QUEUE);
            inform(sCustomer.phoneNumber, "Ð¡×À", sId);
            Table smallTable;
            smallTable.id = sId;
            offer(&SMALL_TABLE_QUEUE, &smallTable, sizeof(Table));
            enterNum += sCustomer.memNum;
            smallTableEnterNum += sCustomer.memNum;
            ++smallTableNum;
            break;
        }
        case MID_TABLE: {
            if (MID_TABLE_USER_QUEUE.size == 0 || MID_TABLE_QUEUE.size >= 20) {
                break;
            }
            Customer mCustomer = *(Customer *) poll(&MID_TABLE_USER_QUEUE);
            int mId = generateId(MID_TABLE, &MID_TABLE_QUEUE);
            inform(mCustomer.phoneNumber, "ÖÐ×À", mId);
            Table midTable;
            midTable.id = mId;
            offer(&MID_TABLE_QUEUE, &midTable, sizeof(Table));
            enterNum += mCustomer.memNum;
            midTableEnterNum += mCustomer.memNum;
            ++midTableNum;
            break;
        }
        case LARGE_TABLE: {
            if (LARGE_TABLE_USER_QUEUE.size == 0 || LARGE_TABLE_QUEUE.size >= 3) {
                break;
            }
            Customer lCustomer = *(Customer *) poll(&LARGE_TABLE_USER_QUEUE);
            int lID = generateId(LARGE_TABLE, &LARGE_TABLE_QUEUE);
            inform(lCustomer.phoneNumber, "´ó×À", lID);
            Table largeTable;
            largeTable.id = lID;
            offer(&LARGE_TABLE_QUEUE, &largeTable, sizeof(Table));
            enterNum += lCustomer.memNum;
            largeTableEnterNum += lCustomer.memNum;
            ++largeTableNum;
        }
        default:
    }
}

void takeTables() {
    while (SMALL_TABLE_USER_QUEUE.size != 0 && SMALL_TABLE_QUEUE.size < 10) {
        takeTable(SMALL_TABLE);
    }
    while (MID_TABLE_USER_QUEUE.size != 0 && MID_TABLE_QUEUE.size < 20) {
        takeTable(MID_TABLE);
    }
    while (LARGE_TABLE_USER_QUEUE.size != 0 && LARGE_TABLE_QUEUE.size < 3) {
        takeTable(LARGE_TABLE);
    }
}

int generateId(int type, void *queue) {
    Queue tableQueue = *(Queue *) queue;
    if (tableQueue.size == 0) {
        return 1;
    }
    switch (type) {
        case 1:
            if ((*(Table*)peekLast(&tableQueue)).id > 9) {
                return 1;
            }
            return (*(Table*)peekLast(&tableQueue)).id + 1;
        case 2:
            if ((*(Table*)peekLast(&tableQueue)).id > 19) {
                return 1;
            }
            return (*(Table*)peekLast(&tableQueue)).id + 1;
        case 3:
            if ((*(Table*)peekLast(&tableQueue)).id > 2) {
                return 1;
            }
            return (*(Table*)peekLast(&tableQueue)).id + 1;
        default:
    }
    return -1;
}

void releaseTable(int sNum, int mNum, int lNum) {
    sNum = sNum < SMALL_TABLE_QUEUE.size ? sNum : SMALL_TABLE_QUEUE.size;
    mNum = mNum < MID_TABLE_QUEUE.size ? mNum : MID_TABLE_QUEUE.size;
    lNum = lNum < LARGE_TABLE_QUEUE.size ? lNum : LARGE_TABLE_QUEUE.size;
    for (int i = 0; i < sNum; i++) {
        poll(&SMALL_TABLE_QUEUE);
    }
    for (int i = 0; i < mNum; i++) {
        poll(&MID_TABLE_QUEUE);
    }
    for (int i = 0; i < lNum; i++) {
        poll(&LARGE_TABLE_QUEUE);
    }
}
