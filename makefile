make all: test1 test2 test3 list.o

list.o : list.c
	gcc -std=c99 -Wall -pedantic -c list.c -o list.o


test1.o : test1.c
	gcc -std=c99 -Wall -pedantic -c test1.c -o test1.o

test1: test1.o list.o 
	gcc -std=c99 -Wall -pedantic -o test1 test1.o list.o 

test2.o : test2.c
	gcc -std=c99 -Wall -pedantic -c test2.c -o test2.o -DLIST

test2: test2.o list.o 
	gcc -std=c99 -Wall -pedantic -o test2 test2.o list.o -DLIST

test3.o : test3.c
	gcc -std=c99 -Wall -pedantic -c test3.c -o test3.o

test3: test3.o list.o 
	gcc -std=c99 -Wall -pedantic -o test3 test3.o list.o 


clean:
	rm test1 test1.o test2 test2.o test3 test3.o list.o