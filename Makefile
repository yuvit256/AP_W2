
CC = gcc
CFLAGS = -Wall -Werror -g
TARGETS = primesCounter randomGenerator
MY_PROGRAM_OBJS = main.o MyPrimeCounter.o
GENERATOR_OBJS = generator.o MyPrimeCounter.o
all: $(TARGETS)
primesCounter: $(MY_PROGRAM_OBJS)
	$(CC) $(CFLAGS) -o primesCounter $(MY_PROGRAM_OBJS) -lm
randomGenerator: $(GENERATOR_OBJS)
	$(CC) $(CFLAGS) -o randomGenerator $(GENERATOR_OBJS) -lm
main.o: main.c MyPrimeCounter.h
	$(CC) $(CFLAGS) -c main.c
MyPrimeCounter.o: MyPrimeCounter.c MyPrimeCounter.h
	$(CC) $(CFLAGS) -c MyPrimeCounter.c
generator.o: generator.c
	$(CC) $(CFLAGS) -c generator.c
clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean

