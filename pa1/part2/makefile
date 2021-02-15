# MACROS
CC = gcc

all: pa1_part2

clean:
	rm -f pa1_part2 *.o

pa1_part1: pa1_part2.o
	$(CC) pa1_part2.o -o pa1_part2
pa1_part1.o: pa1_part2.c
	$(CC) -c pa1_part2.c