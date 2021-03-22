CC = g++
CFLAGS = -Wall -g

main: main.o parser.o
	$(CC) $(CFLAGS) -o main main.o parser.o

main.o: main.cpp parser.h
	$(CC) $(CFLAGS) -c main.cpp

parser.o: parser.h