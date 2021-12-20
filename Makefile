CC=gcc
FLAGS= -Wall -g

all: stringProg
.PHONY: clean

stringProg: main.o
	$(CC) $(FLAGS) -o stringProg main.c

main.o: main.c
	$(CC) $(FLAGS) -c main.c

clean:
	rm -f *.o *.a *.so *.out