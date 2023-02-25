//
// Created by MashiroT on 2023/2/24.
//

#include "file.h"
#include "data.h"

extern int enterNum;
extern int totalNum;
extern int smallTableNum;
extern int midTableNum;
extern int largeTableNum;
extern int smallTableEnterNum;
extern int midTableEnterNum;
extern int largeTableEnterNum;
extern pthread_t thread;

void output() {
    // 获取当前时间
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    char filename[20];
    // 将当前时间格式化为 yyyy_MM_dd
    sprintf(filename, "./Data/%04d_%02d_%02d.dat", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
    // 创建 Data 文件夹
    mkdir("./Data");
    // 打开文件并以二进制写入形式写入变量
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("无法打开待写入文件\n");
        return;
    }
    fwrite(&enterNum, sizeof(int), 1, fp);
    fwrite(&totalNum, sizeof(int), 1, fp);
    fwrite(&smallTableNum, sizeof(int), 1, fp);
    fwrite(&midTableNum, sizeof(int), 1, fp);
    fwrite(&largeTableNum, sizeof(int), 1, fp);
    fwrite(&smallTableEnterNum, sizeof(int), 1, fp);
    fwrite(&midTableEnterNum, sizeof(int), 1, fp);
    fwrite(&largeTableEnterNum, sizeof(int), 1, fp);
    fclose(fp);
}

void *timer_thread() {
    while (1) {
        time_t now = time(NULL);
        struct tm *local_time = localtime(&now);
        // 如果是 00:00 点
        if (local_time->tm_hour == 0 && local_time->tm_min == 0) {
            output();
            printf("今日统计数据已经导出\n");
            resetStatisticalData();
        }
        // 等待 1 分钟
        sleep(60);
    }
}

Data deserialize(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "打开文件失败: %s\n", filename);
        Data rs;
        rs.totalNum = -1;
        return rs;
    }
    Data data;
    fread(&data, sizeof(Data), 1, fp);
    fclose(fp);
    return data;
}