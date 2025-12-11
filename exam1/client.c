#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <string.h>
#include "common.h"

// Synopsis: ./client "Message" Amount
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Message> <Amount>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *msg = argv[1];
    int amount = atoi(argv[2]);

    // Open existing resources
    int fd = shm_open(SHM_NAME, O_RDWR, 0);
    if (fd == -1) { perror("shm_open"); exit(EXIT_FAILURE); }
    
    transaction_t *shmp = mmap(NULL, sizeof(transaction_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED) { perror("mmap"); exit(EXIT_FAILURE); }

    sem_t *sem_req = sem_open(SEM_REQUEST_NAME, 0);
    sem_t *sem_res = sem_open(SEM_RESPONSE_NAME, 0);
    sem_t *sem_trans = sem_open(SEM_TRANSACTION_NAME, 0);

    if (sem_req == SEM_FAILED || sem_res == SEM_FAILED || sem_trans == SEM_FAILED) {
        perror("sem_open"); exit(EXIT_FAILURE);
    }

    printf("[Client] Waiting for transaction slot...\n");
    // 1. Wait for transaction semaphore [cite: 37]
    sem_wait(sem_trans);

    // 2. Write to shared memory [cite: 38]
    printf("[Client] Sending request: %s (%d)\n", msg, amount);
    shmp->amount = amount;
    strncpy(shmp->message, msg, 255);

    // 3. Post request semaphore [cite: 39]
    sem_post(sem_req);

    // 4. Wait for response [cite: 44]
    printf("[Client] Waiting for server response...\n");
    sem_wait(sem_res);

    // 5. Read response [cite: 45]
    if (shmp->status == TRANSACTION_STATUS_SUCCESS) {
        printf("[Client] SUCCESS. New Balance inferred via server logs.\n");
    } else {
        printf("[Client] FAILED. Transaction rejected.\n");
    }

    // 6. Post transaction semaphore [cite: 46]
    sem_post(sem_trans);

    return EXIT_SUCCESS;
}
