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
        printf("##########餐饮业排队叫号系统##########\n");
        printf("1. 取号\n");
        printf("2. 候餐人数\n");
        printf("3. 管理后台\n");
        printf("0. 退出\n");
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
                printf(" 输入有误，重新输入\n");
                printf("-----------------\n");
        }
    }
}

void managePage() {
    while (1) {
        printf("##########管理界面##########\n");
        printf("1. 查看实时餐位使用情况\n");
        printf("2. 查看近日餐位使用情况\n");
        printf("3. 清理桌子\n");
        printf("4. 立刻导出今日数据 (测试用, 会重置统计数据)\n");
        printf("0. 返回\n");
        printf("###########################\n");
        int cmd = 0;
        scanf("%d", &cmd);
        switch (cmd) {
            case 1: {
                printf("##########实时使用情况##########\n");
                printf("店内桌数: %d\n", SMALL_TABLE_QUEUE.size + MID_TABLE_QUEUE.size + LARGE_TABLE_QUEUE.size);
                printf("使用 || 小桌: %d \t 中桌: %d \t 大桌: %d\n", SMALL_TABLE_QUEUE.size, MID_TABLE_QUEUE.size,
                       LARGE_TABLE_QUEUE.size);
                printf("空闲 || 小桌: %d \t 中桌: %d \t 大桌: %d\n", (10 - SMALL_TABLE_QUEUE.size),
                       (20 - MID_TABLE_QUEUE.size), (3 - LARGE_TABLE_QUEUE.size));
                printf("---\n");
                printf("候餐人数: %d\n",
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
                    perror("打开目录失败");
                    break;
                }

                if (fileCount == 0) {
                    printf("暂无统计数据文件\n");
                    printf("0. 返回\n");
                    getchar();
                    getchar();
                    break;
                }

                for (int i = 0; i < fileCount; i++) {
                    char fileName[256];
                    sprintf(fileName, "%s/%s", path, files[i]);
                    FILE *fp = fopen(fileName, "rb");
                    if (fp == NULL) {
                        printf("打开文件失败");
                        break;
                    }
                    Data data;
                    fread(&data, sizeof(Data), 1, fp);
                    fclose(fp);
//                    printf("%s:\n 进店人数: %d, 总人数: %d | 桌数 小桌: %d, 中桌: %d, 大桌: %d | 入座人数 小桌: %d, 中桌: %d, 大桌: %d | 上座率 小桌: %.2lf, 中桌: %.2lf, 大桌: %.2lf\n",
                    printf("%s:\n 进店人数: %d, 总人数: %d | 上座率 小桌: %.2lf, 中桌: %.2lf, 大桌: %.2lf\n",
                           files[i], data.enterNum, data.totalNum,
                           data.smallTableNum == 0 ? 0 : data.smallTableEnterNum /
                                                         (double) (data.smallTableNum * SMALL_TABLE_CAPACITY),
                           data.midTableNum == 0 ? 0 : data.midTableEnterNum /
                                                       (double) (data.midTableNum * MID_TABLE_CAPACITY),
                           data.largeTableNum == 0 ? 0 : data.largeTableEnterNum /
                                                         (double) (data.largeTableNum * LARGE_TABLE_CAPACITY));
                }
                printf("==========\n");
                printf("0. 返回\n");
                getchar();
                getchar();
                break;
            }
            case 4: {
                output();
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
            }
                break;
            case 0:
                return;
            default: {
                printf("-----------------\n");
                printf(" 输入有误，重新输入\n");
                printf("-----------------\n");
            }
        }
    }
}

void statusPage() {
    printf("##########候餐人数##########\n");
    printf("小桌: %d 桌\n", SMALL_TABLE_USER_QUEUE.size);
    printf("中桌: %d 桌\n", MID_TABLE_USER_QUEUE.size);
    printf("大桌: %d 桌\n", LARGE_TABLE_USER_QUEUE.size);
    printf("###########################\n");
    printf("0. 返回\n");
    getchar();
    getchar();
}

void takeTokenPage() {
    Customer customer;
    printf("###########取号界面##########\n");
    while (1) {
        printf("请输入就餐人数：\n");
        int memNum = 0;
        scanf("%d", &memNum);
        if (memNum < 0 || memNum > LARGE_TABLE_CAPACITY) {
            printf("格式有误, 请重新输入, 或输入 0 退出\n");
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
        printf("请输入联系方式：\n");
        char telephoneNum[11] = {0};
        scanf("%s", telephoneNum);
        if (strcmp("0", telephoneNum) == 0) {
            return;
        }
        if (isValidPhoneNumber(telephoneNum)) {
            customer.phoneNumber = telephoneNum;
            break;
        }
        printf("格式有误, 请重新输入, 或输入 0 退出\n");
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
    printf("亲爱的 %s, 您已取号成功, 请耐心等待, 前面还有 %d 桌\n", lastFourNum, waitNum);
    takeTable(customer.type);
    totalNum += customer.memNum;
}