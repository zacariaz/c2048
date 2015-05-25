all:
	cc -c -o c2048.o c2048.c
	cc -c -o main.o main.c
	cc -o c2048 main.o c2048.o -l ncurses -std=c11 -Wall -pedantic -Wsign-compare
