CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lrt -pthread

all: transaction_server client

transaction_server: transaction_server.c transaction_server.h common.h
	$(CC) $(CFLAGS) -o transaction_server transaction_server.c $(LDFLAGS)

client: client.c common.h
	$(CC) $(CFLAGS) -o client client.c $(LDFLAGS)

clean:
	rm -f transaction_server client history.txt

# Helper to remove stuck resources [cite: 10]
cleanup:
	rm -f /dev/shm/bs_bank_shm
	rm -f /dev/shm/sem.bs_sem_*
