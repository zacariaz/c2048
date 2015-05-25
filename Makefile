OBJS = main.o c2048.o
CC = cc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -Wextra
LDLIBS = -l ncurses

all:
	$(CC) -c -o c2048.o c2048.c $(CFLAGS)
	$(CC) -c -o main.o main.c $(CFLAGS)
	$(CC) -o c2048 main.o c2048.o $(LDLIBS) $(CFLAGS)
