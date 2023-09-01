# Execute your driver1 program. Enter at least 6 students. Select each of other options at least once.
# Then, copy/paste your outputs from screen into driver1_output.txt..
# Also run your program with valgrind driver1, and make sure there is no memory leakages at the end!

CC = gcc
CFLAGS = -Wall -g

all: driver1 

clean:
	rm -f *.o driver1
output:
	valgrind ./driver1 < driver1_input.txt > driver1_output.txt
run:
	./driver1
mylinkedlist.o: mylinkedlist.c mylinkedlist.h
	$(CC) $(CFLAGS) -c mylinkedlist.c

driver1.o: driver1.c mylinkedlist.h
	$(CC) $(CFLAGS) -c driver1.c

driver1: driver1.o mylinkedlist.o
	$(CC) $(CFLAGS) -o driver1 driver1.o mylinkedlist.o

