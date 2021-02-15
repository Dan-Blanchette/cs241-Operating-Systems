# MACROS
CC = gcc

all: pa1_part1

clean:
	rm -f pa1_part1 *.o

pa1_part1: pa1_part1.o
	$(CC) pa1_part1.o -o pa1_part1
pa1_part1.o: pa1_part1.c
	$(CC) -c pa1_part1.c