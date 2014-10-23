all: find
	
find: find.o
	gcc find.o -o find

find.o: find.c
	gcc -c find.c

clean:
	rm -f *.o