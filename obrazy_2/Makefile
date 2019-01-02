__start__: a.out
		./a.out

a.out: main.o funkcje.o
		gcc main.o funkcje.o -lm

main.o: main.c funkcje.h 
		gcc -c -Wall main.c -lm

funkcje.o: funkcje.h funkcje.c 
		gcc -c -Wall funkcje.c -lm
