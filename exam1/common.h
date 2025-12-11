#ifndef COMMON_H
#define COMMON_H

#include <semaphore.h>

// Shared Memory and Semaphore Names
#define SHM_NAME "/bs_bank_shm"
#define SEM_REQUEST_NAME "/bs_sem_request"
#define SEM_RESPONSE_NAME "/bs_sem_response"
#define SEM_TRANSACTION_NAME "/bs_sem_transaction"

// Permissions
#define PERMISSIONS 0600

// Status Codes
#define TRANSACTION_STATUS_SUCCESS 0
#define TRANSACTION_STATUS_FAILED -1

// Data Structure in Shared Memory [cite: 83]
typedef struct {
    int id;                 // Transaction ID
    int amount;             // Amount to transfer
    int status;             // Status of operation
    char message[256];      // Transaction message
    int current_balance;    // Current balance (set by server)
} transaction_t;

#endif
