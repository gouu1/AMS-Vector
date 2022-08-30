CC = gcc
CFLAGS = -Wall -pedantic

shm: shm_ipc.o
	$(CC) $(CFLAGS) -lrt -lpthread -o shm shm_ipc.c