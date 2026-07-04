#include <stdio.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t mutex; // dung de bao ve vung tranh chap quanh bien x

void* processA(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20) x = 0;
        printf("[A] x = %d\n", x);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* processB(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20) x = 0;
        printf("[B] x = %d\n", x);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);

    pthread_t tA, tB;
    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}

/*
 * NHAN XET:
 * Sau khi bao ve doan lenh "doc-cong-ghi" tren bien x bang pthread_mutex_lock/
 * unlock, tai 1 thoi diem chi 1 trong 2 thread duoc phep thuc hien va in ra
 * gia tri x. Nho vay khong con hien tuong mat cap nhat, gia tri x se tang
 * tuan tu tu 0 den 19 roi quay ve 0, dung nhu mong doi (du thu tu xen ke
 * giua A va B co the thay doi qua moi lan chay, nhung tinh dung dan cua gia
 * tri x luon duoc dam bao).
 */
