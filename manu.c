//
// Created by MashiroT on 2023/2/24.
//

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "manu.h"
#include "manage.h"
#include "file.h"
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

void homePage() {
    while (1) {
        printf("##########����ҵ�Ŷӽк�ϵͳ##########\n");
        printf("1. ȡ��\n");
        printf("2. �������\n");
        printf("3. �����̨\n");
        printf("0. �˳�\n");
        printf("###################################\n");
        int cmd = 0;
        scanf("%d", &cmd);
        switch (cmd) {
            case 1:
                takeTokenPage();
                break;
            case 2:
                statusPage();
                break;
            case 3:
                managePage();
                takeTables();
                break;
            case 0:
                return;
            default:
                printf("-----------------\n");
                printf(" ����������������\n");
                printf("-----------------\n");
        }
    }
}

void managePage() {
    while (1) {
        printf("##########�������##########\n");
        printf("1. �鿴ʵʱ��λʹ�����\n");
        printf("2. �鿴���ղ�λʹ�����\n");
        printf("3. ��������\n");
        printf("4. ���̵����������� (������, ������ͳ������)\n");
        printf("0. ����\n");
        printf("###########################\n");
        int cmd = 0;
        scanf("%d", &cmd);
        switch (cmd) {
            case 1: {
                printf("##########ʵʱʹ�����##########\n");
                printf("��������: %d\n", SMALL_TABLE_QUEUE.size + MID_TABLE_QUEUE.size + LARGE_TABLE_QUEUE.size);
                printf("ʹ�� || С��: %d \t ����: %d \t ����: %d\n", SMALL_TABLE_QUEUE.size, MID_TABLE_QUEUE.size,
                       LARGE_TABLE_QUEUE.size);
                printf("���� || С��: %d \t ����: %d \t ����: %d\n", (10 - SMALL_TABLE_QUEUE.size),
                       (20 - MID_TABLE_QUEUE.size), (3 - LARGE_TABLE_QUEUE.size));
                printf("---\n");
                printf("�������: %d\n",
                       SMALL_TABLE_USER_QUEUE.size + MID_TABLE_USER_QUEUE.size + LARGE_TABLE_USER_QUEUE.size);
                printf("##############################\n");
            }
                break;
            case 2: {
                DIR *folder;
                struct dirent *file;
                char *path = "./Data";
                char files[100][256];
                int fileCount = 0;

                if ((folder = opendir(path)) != NULL) {
                    while ((file = readdir(folder)) != NULL) {
                        if (strstr(file->d_name, ".dat") != NULL) {
                            strcpy(files[fileCount++], file->d_name);
                        }
                    }
                    closedir(folder);
                } else {
                    perror("��Ŀ¼ʧ��");
                    break;
                }

                if (fileCount == 0) {
                    printf("����ͳ�������ļ�\n");
                    printf("0. ����\n");
                    getchar();
                    getchar();
                    break;
                }

                printf("Ŀǰ�� %d ���ͳ������, �ֱ��ǣ�\n", fileCount);
                for (int i = 0; i < fileCount; i++) {
                    printf("%d: %s", i + 1, files[i]);
                    if (i + 1 < fileCount) {
                        printf(", ");
                    }
                    if (i > 0 && i / 5 == 0) {
                    }
                }
                printf("\n");
                int start = 0;
                int end = fileCount;
                while (1) {
                    printf("������ʱ��ε����(����), ��ʽ: 1, 2\n");
                    scanf("%d, %d", &start, &end);
                    if (start >= 1 && end <= fileCount && start >= end){
                        --start;
                        if (isValidDateRange(*files, start, end)) {
                            break;
                        }
                    }
                    printf("��ʽ��������������\n");
                }

                for (int i = start; i < end; i++) {
                    char fileName[256];
                    sprintf(fileName, "%s/%s", path, files[i]);
                    FILE *fp = fopen(fileName, "rb");
                    if (fp == NULL) {
                        printf("���ļ�ʧ��");
                        break;
                    }
                    Data data;
                    fread(&data, sizeof(Data), 1, fp);
                    fclose(fp);
//                    printf("%s:\n ��������: %d, ������: %d | ���� С��: %d, ����: %d, ����: %d | �������� С��: %d, ����: %d, ����: %d | ������ С��: %.2lf, ����: %.2lf, ����: %.2lf\n",
                    printf("%s:\n ��������: %d, ������: %d | ������ С��: %.2lf, ����: %.2lf, ����: %.2lf\n",
                           files[i], data.enterNum, data.totalNum,
                           data.smallTableNum == 0 ? 0 : data.smallTableEnterNum /
                                                         (double) (data.smallTableNum * SMALL_TABLE_CAPACITY),
                           data.midTableNum == 0 ? 0 : data.midTableEnterNum /
                                                       (double) (data.midTableNum * MID_TABLE_CAPACITY),
                           data.largeTableNum == 0 ? 0 : data.largeTableEnterNum /
                                                         (double) (data.largeTableNum * LARGE_TABLE_CAPACITY));
                }
                printf("==========\n");
                printf("0. ����\n");
                getchar();
                getchar();
                break;
            }
            case 4: {
                output();
                break;
            }
            case 3: {
                int sNum = 0;
                int mNum = 0;
                int lNum = 0;
                if (SMALL_TABLE_QUEUE.size != 0) {
                    sNum = rand() % SMALL_TABLE_QUEUE.size;
                }
                if (MID_TABLE_QUEUE.size != 0) {
                    mNum = rand() % MID_TABLE_QUEUE.size;
                }
                if (LARGE_TABLE_QUEUE.size != 0) {
                    lNum = rand() % LARGE_TABLE_QUEUE.size;
                }
                releaseTable(sNum, mNum, lNum);
                printf("������ С����%d, ������%d, ����: %d\n", sNum, mNum, lNum);
            }
                break;
            case 0:
                return;
            default: {
                printf("-----------------\n");
                printf(" ����������������\n");
                printf("-----------------\n");
            }
        }
    }
}

void statusPage() {
    printf("##########�������##########\n");
    printf("С��: %d ��\n", SMALL_TABLE_USER_QUEUE.size);
    printf("����: %d ��\n", MID_TABLE_USER_QUEUE.size);
    printf("����: %d ��\n", LARGE_TABLE_USER_QUEUE.size);
    printf("###########################\n");
    printf("0. ����\n");
    getchar();
    getchar();
}

void takeTokenPage() {
    Customer customer;
    printf("###########ȡ�Ž���##########\n");
    while (1) {
        printf("������Ͳ�������\n");
        int memNum = 0;
        scanf("%d", &memNum);
        if (memNum < 0 || memNum > LARGE_TABLE_CAPACITY) {
            printf("��ʽ����, ����������, ������ 0 �˳�\n");
            continue;
        }
        if (memNum == 0) {
            return;
        }
        if (memNum <= SMALL_TABLE_CAPACITY) {
            customer.type = SMALL_TABLE;
        } else if (memNum <= MID_TABLE_CAPACITY) {
            customer.type = MID_TABLE;
        } else {
            customer.type = LARGE_TABLE;
        }
        customer.memNum = memNum;
        break;
    }
    while (1) {
        printf("��������ϵ��ʽ��\n");
        char telephoneNum[11] = {0};
        scanf("%s", telephoneNum);
        if (strcmp("0", telephoneNum) == 0) {
            return;
        }
        if (isValidPhoneNumber(telephoneNum)) {
            customer.phoneNumber = telephoneNum;
            break;
        }
        printf("��ʽ����, ����������, ������ 0 �˳�\n");
    }
    int waitNum = 0;
    switch (customer.type) {
        case SMALL_TABLE:
            waitNum = SMALL_TABLE_USER_QUEUE.size;
            offer(&SMALL_TABLE_USER_QUEUE, &customer, sizeof(Customer));
            break;
        case MID_TABLE:
            waitNum = MID_TABLE_USER_QUEUE.size;
            offer(&MID_TABLE_USER_QUEUE, &customer, sizeof(Customer));
            break;
        case LARGE_TABLE:
            waitNum = LARGE_TABLE_USER_QUEUE.size;
            offer(&LARGE_TABLE_USER_QUEUE, &customer, sizeof(Customer));
        default:
    }
    char lastFourNum[4] = {};
    strncpy(lastFourNum, &customer.phoneNumber[7], 0);
    printf("�װ��� %s, ����ȡ�ųɹ�, �����ĵȴ�, ǰ�滹�� %d ��\n", lastFourNum, waitNum);
    takeTable(customer.type);
    totalNum += customer.memNum;
}