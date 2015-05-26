OBJS = main.o c2048.o tui.o
CC = gcc
CFLAGS = -x c -std=c11 -Wall -Wextra -pedantic -Wextra
LDLIBS = -l ncurses

c2048 : $(OBJS)
	$(CC) -o c2048 $(OBJS) $(CFLAGS) $(LDLIBS)

main.o : main.h
c2048.o : c2048.h
tui.o : tui.h
