#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define N 100

int a[N];
int count = 0;    // so phan tu hien co trong a
sem_t sem_mutex;  // semaphore nhi phan bao ve vung tranh chap (a[] va count)

void* producer(void* arg) {
    unsigned int seed = time(NULL);
    while (1) {
        int value = rand_r(&seed) % 1000;

        sem_wait(&sem_mutex);          // vao vung tranh chap
        if (count < N) {
            a[count] = value;
            count++;
            printf("[Producer] Them %d -> so phan tu trong a: %d\n", value, count);
        } else {
            printf("[Producer] Mang day, khong the them %d\n", value);
        }
        sem_post(&sem_mutex);          // roi vung tranh chap

        usleep(300000);
    }
    return NULL;
}

void* consumer(void* arg) {
    unsigned int seed = time(NULL) ^ 12345;
    while (1) {
        sem_wait(&sem_mutex);
        if (count == 0) {
            printf("[Consumer] Nothing in array a\n");
        } else {
            int index = rand_r(&seed) % count;
            int value = a[index];
            a[index] = a[count - 1];
            count--;
            printf("[Consumer] Lay %d (vi tri %d) -> so phan tu con lai: %d\n", value, index, count);
        }
        sem_post(&sem_mutex);

        usleep(500000);
    }
    return NULL;
}

int main() {
    sem_init(&sem_mutex, 0, 1); // gia tri 1 -> hoat dong nhu 1 mutex (chi 1 thread vao vung tranh chap tai 1 thoi diem)

    pthread_t tp, tc;
    pthread_create(&tp, NULL, producer, NULL);
    pthread_create(&tc, NULL, consumer, NULL);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);

    sem_destroy(&sem_mutex);
    return 0;
}
