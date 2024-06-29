.PHONY: all
all: generator primeCounter MyPrimeCounter

generator:  generator.c
	gcc -o randomGenerator generator.c

primeCounter:	primeCounter.c
	gcc -o primeCounter primeCounter.c

MyPrimeCounter:  MyPrimeCounter.c
	gcc -o MyPrimeCounter MyPrimeCounter.c -lm

.PHONY: clean
clean:
	-rm randomGenerator primeCounter MyPrimeCounter 2>/dev/null
