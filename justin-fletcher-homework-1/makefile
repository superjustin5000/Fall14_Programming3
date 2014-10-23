all: bstsort
	
bstsort: bstsort.o
	gcc bstsort.o -o bstsort

bstsort.o: bstsort.c
	gcc -c bstsort.c

clean:
	rm -f bstsort.o
	rm -f bstsort
	rm -f *.txt;