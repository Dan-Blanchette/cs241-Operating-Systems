CC = gcc
FLAGS = -Werror

all: shell

clobber: clean
	rm -f *~\#*\#
clean:
	rm -f shell *.o

shell: main.o shell.o
	$(CC) $(-Werror) main.o shell.o -o shell
main.o: main.c shell.h
	$(CC) -c main.c
shell.o: shell.c shell.h
	$(CC) -c shell.c