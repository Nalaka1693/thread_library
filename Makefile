CFLAGS=-I./ -Wall -Wstrict-prototypes -Werror
CC=gcc

all: main

main: queue.o lib.o switch.o main.o
	gcc queue.o main.o lib.o switch.o -o main -m64 -static

%.o:%.c
	$(CC) $(CFLAGS) -c $? -o $@ -m64 -static -g
%.o:%.S
	$(CC) $(CFLAGS) -c $? -o $@ -m64 -static -g

clean:
	rm -f *.o *.out main *~
