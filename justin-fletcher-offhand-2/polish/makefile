all: polish
	
polish: main.o getch.o getop.o stack.o
	gcc main.o getch.o getop.o stack.o -o polish

main.o: main.c
	gcc -c main.c

getch.o: getch.c
	gcc -c getch.c

getop.o: getop.c
	gcc -c getop.c

stack.o: stack.c
	gcc -c stack.c

clean:
	rm -f *.o
