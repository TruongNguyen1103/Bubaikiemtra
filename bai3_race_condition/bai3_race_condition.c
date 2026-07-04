#include <stdio.h>
#include <pthread.h>

int x = 0; // bien toan cuc dung chung, CHUA duoc bao ve

void* processA(void* arg) {
    while (1) {
        x = x + 1;
        if (x == 20) x = 0;
        printf("[A] x = %d\n", x);
    }
    return NULL;
}

void* processB(void* arg) {
    while (1) {
        x = x + 1;
        if (x == 20) x = 0;
        printf("[B] x = %d\n", x);
    }
    return NULL;
}

int main() {
    pthread_t tA, tB;
    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    return 0;
}

/*
 * NHAN XET:
 * Lenh "x = x + 1" khong phai la lenh nguyen tu (atomic), no thuc chat gom
 * 3 buoc: doc x -> cong 1 -> ghi lai x. Vi 2 thread chay song song va cung
 * truy xuat vao 1 bien x dung chung ma KHONG duoc dong bo, nen co the xay ra
 * tinh huong ca 2 thread cung doc duoc 1 gia tri x giong nhau roi cung ghi de
 * len nhau -> ket qua bi MAT MAT CAP NHAT (lost update). Chay thu se thay
 * gia tri x in ra co the bi lap lai, nhay cach quang, hoac tang khong dung
 * theo thu tu tuan tu 0..19 nhu mong doi.
 */
