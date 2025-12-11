#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "common.h"
#include "transaction_server.h"

// Global Variables
int shmfd;
transaction_t *shmp;
sem_t *sem_request;
sem_t *sem_response;
sem_t *sem_transaction;
FILE *fp_out;

// Helper function for error handling
void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Helper function for usage
void usage(char *msg) {
    if (msg) fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "Usage: ./transaction_server [-b BALANCE] [HISTORY]\n");
    exit(EXIT_FAILURE);
}

// --- TASK 1: Argument Parsing (30 Points) --- [cite: 47]
void parse_arguments(int argc, char *argv[], struct arguments *args) {
    // [cite: 52, 53] Default balance is 0.
    // [cite: 56] Default history path is "history.txt".
    
    // TODO: Implement argument parsing using getopt[cite: 60].
    // - Check for -b flag. Convert using strtol[cite: 61].
    // - Ensure balance is a positive integer (b >= 0)[cite: 52].
    // - Handle optional positional argument for history file[cite: 55].
    // - Call usage() on error[cite: 57].
}

// --- TASK 2: Resource Allocation (35 Points) --- [cite: 73]
void allocate_resources(const char *path) {
    // TODO: Create POSIX Shared Memory[cite: 76].
    // - Use shm_open with O_CREAT | O_RDWR | O_EXCL (fail if exists)[cite: 84].
    // - Set size using ftruncate[cite: 90].
    // - Map memory using mmap[cite: 77].

    // TODO: Create 3 POSIX Named Semaphores[cite: 80].
    // - sem_request, sem_response, sem_transaction.
    // - Initialize with correct values for the protocol[cite: 81].
    //   Hint: Client waits on transaction first, server waits on request.

    // TODO: Open history file for writing[cite: 85].
    // - Store file pointer in global 'fp_out'.
    
    // On any error, call error_exit[cite: 86].
}

// --- TASK 3: Transaction Processing (35 Points) --- [cite: 91]
void process_transactions(int balance) {
    int current_id = 0;
    int current_balance = balance;

    // TODO: Implement the server loop[cite: 94].
    while (1) {
        // 1. Wait for request from client[cite: 96].
        
        // 2. Validate Transaction[cite: 97].
        // - Valid if: (balance + amount >= 0) AND (amount != 0).
        
        // 3. If Valid:
        // - Write CSV line to fp_out: <id>;<amount>;<old_bal>;<new_bal>;<msg>[cite: 100].
        // - Update balance and current_id[cite: 104].
        // - Set shmp->status = TRANSACTION_STATUS_SUCCESS.
        
        // 4. If Invalid:
        // - Set shmp->status = TRANSACTION_STATUS_FAILED[cite: 105].
        // - Do NOT write to file. ID remains unchanged.

        // 5. Signal client that response is ready[cite: 107].
        
        // Flush file stream to ensure data is written
        fflush(fp_out);
    }
}

// Main Function
int main(int argc, char *argv[]) {
    struct arguments args;
    
    // Initialize defaults
    args.balance = 0;
    args.history_path = "history.txt";

    parse_arguments(argc, argv, &args);
    allocate_resources(args.history_path);
    
    printf("Server started. Balance: %d, History: %s\n", args.balance, args.history_path);
    
    process_transactions(args.balance);

    return EXIT_SUCCESS;
}

// Cleanup helper (not strictly part of the test logic but good for testing)
void cleanup() {
    sem_unlink(SEM_REQUEST_NAME);
    sem_unlink(SEM_RESPONSE_NAME);
    sem_unlink(SEM_TRANSACTION_NAME);
    shm_unlink(SHM_NAME);
}
