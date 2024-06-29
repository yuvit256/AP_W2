# AP_W2
# Prime Number Counter and Generator

## Overview

This project consists of a prime number counter and generator implemented in C. The provided files include:
- `MyPrimeCounter.c`: The main program to count prime numbers.
- `generator.c`: A program to generate prime numbers.
- `Makefile`: A Makefile to compile the programs.

## Files

### MyPrimeCounter.c

This file contains the implementation of a program that counts prime numbers within a specified range. It uses a algorithm to check for primality and counts the number of prime numbers found and uses threads.

### generator.c

This file contains the implementation of a program that generates prime numbers up to a specified limit. It outputs the prime numbers to the console.

### Makefile

This file contains the build instructions for the project. It includes targets to compile the `MyPrimeCounter.c` and `generator.c` programs, as well as clean up build artifacts.

## Usage

### Compilation

To compile the programs, run the command in the project directory:

```sh
make
```
example of how to run the programs, run the command in the project directory:
```sh
./randomGenerator 10 10000000 | ./MyPrimeCounter

```
examples of running:

<Cd>

![with improve the isPrime](https://github.com/ron12120/AP_W2/assets/76705730/e33656d7-b3b5-49d1-b053-7f54a947beba)

![without improve isPrime](https://github.com/ron12120/AP_W2/assets/76705730/d24566b3-ef07-4bb9-bf88-37a9b51fa8a2)

