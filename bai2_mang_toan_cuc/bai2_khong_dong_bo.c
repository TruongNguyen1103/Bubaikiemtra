#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/*
 * BAN CHUA DONG BO - dung de chay thu va quan sat loi:
 *   - count co the bi sai (2 thread cung doc/ghi dong thoi -> mat du lieu)
 *   - co the truy xuat a[] khong hop le (vd doc count==0 nhung van tru vao)
 */

#define N 100

int a[N];
int count = 0; // so phan tu hien co trong a

void* producer(void* arg) {
    unsigned int seed = time(NULL);
    while (1) {
        int value = rand_r(&seed) % 1000;

        if (count < N) {
            a[count] = value;
            count++;
            printf("[Producer] Them %d -> so phan tu trong a: %d\n", value, count);
        } else {
            printf("[Producer] Mang day, khong the them %d\n", value);
        }

        usleep(300000);
    }
    return NULL;
}

void* consumer(void* arg) {
    unsigned int seed = time(NULL) ^ 12345;
    while (1) {
        if (count == 0) {
            printf("[Consumer] Nothing in array a\n");
        } else {
            int index = rand_r(&seed) % count;
            int value = a[index];
            a[index] = a[count - 1];
            count--;
            printf("[Consumer] Lay %d (vi tri %d) -> so phan tu con lai: %d\n", value, index, count);
        }

        usleep(500000);
    }
    return NULL;
}

int main() {
    pthread_t tp, tc;
    pthread_create(&tp, NULL, producer, NULL);
    pthread_create(&tc, NULL, consumer, NULL);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);
    return 0;
}
