CC = gcc
CFLAGS = -Wall -pedantic # Show all reasonable warnings
LDFLAGS =

all: dbl_vector

dbl_vector: dbl_test.o dbl_vector.o

dbl_test.o: dbl_test.c

dbl_vector.o: dbl_vector.c

clean:
	rm -f dbl *.o

.PHONY: all clean
