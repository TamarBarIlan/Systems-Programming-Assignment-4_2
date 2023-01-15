CC=gcc
AR=ar
FLAGS= -Wall -g

all: graph
graph: main.o graph.o
	$(CC) $(FLAGS) -o graph main.o graph.o
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c
graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c
.PHONY: clean all
clean:
	rm -f *.o *.so graph