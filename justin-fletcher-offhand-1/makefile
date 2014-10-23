all: sizeof temp
	
sizeof: sizeof.o
	gcc sizeof.o -o sizeof

temp: test.o
	gcc test.o -o temp

sizeof.o: sizeof.c
	gcc -c sizeof.c

test.o: test.c
	gcc -c test.c
