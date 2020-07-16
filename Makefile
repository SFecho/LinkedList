CC = gcc

all: linked_list test main

linked_list: LinkedList.c
	$(CC) -Wall -c LinkedList.c -g -o LinkedList.o

test: test.c
	$(CC) -Wall -c test.c -g -o test.o
    
main: LinkedList.o test.o
	$(CC) -Wall LinkedList.o test.o -g -o test