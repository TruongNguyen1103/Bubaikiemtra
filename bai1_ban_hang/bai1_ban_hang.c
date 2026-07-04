#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/*
 * Bai 1: dieu kien can dam bao:  sells <= products <= sells + K
 *   voi K = [2 so cuoi cua MSSV] + 10
 *
 * ***** THAY SO 10 O DONG DUOI DAY BANG 2 SO CUOI MSSV CUA BAN *****
 */
#define MSSV_2SO_CUOI 41   /* MSSV: CT240041 -> 2 so cuoi = 41 */
#define K (MSSV_2SO_CUOI + 10)

int sells = 0, products = 0;

sem_t sem_sell;     // dem so hang dang co san de ban  (= products - sells)
sem_t sem_produce;  // dem so "cho trong" con duoc phep san xuat them (= K - (products - sells))

void* processA(void* arg) { // ban hang
    while (1) {
        sem_wait(&sem_sell);       // cho neu chua co hang de ban
        sells++;
        printf("[A - Ban hang ] sells = %d, products = %d\n", sells, products);
        sem_post(&sem_produce);    // bao hieu vua giai phong 1 "cho trong" de san xuat tiep
    }
    return NULL;
}

void* processB(void* arg) { // san xuat
    while (1) {
        sem_wait(&sem_produce);    // cho neu da san xuat toi han (products - sells == K)
        products++;
        printf("[B - San xuat ] sells = %d, products = %d\n", sells, products);
        sem_post(&sem_sell);       // bao hieu vua co them 1 hang de ban
    }
    return NULL;
}

int main() {
    sem_init(&sem_sell, 0, 0);   // ban dau chua co hang de ban
    sem_init(&sem_produce, 0, K); // ban dau duoc phep san xuat truoc toi da K don vi

    pthread_t tA, tB;
    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    sem_destroy(&sem_sell);
    sem_destroy(&sem_produce);
    return 0;
}
