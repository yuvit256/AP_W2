#ifndef MY_PRIME_COUNTER
#define MY_PRIME_COUNTER

#include <stdio.h>      // For input/output operations
#include <stdlib.h>     // For standard library functions
#include <math.h>       // For mathematical functions
#include <pthread.h>    // For POSIX threads
#include <stdbool.h>


#define PRIMES_ARRAY_LIMIT 45830 // The limit for the prime numbers array

// Global variables
extern int array_size_of_primes;           // The size of the array of prime numbers
extern int *array_of_prime_numbers;        // Pointer to the array of prime numbers
extern int *how_much_threads;              // Pointer to the number of threads
extern pthread_t *thread_list;             // Pointer to the list of threads

// Function declarations
bool check_if_number_is_prime_standard(int, int);
void create_list_of_primes_for_threads();
bool isPrime(int);
int count_how_many_primes_were();
void* thread_task_for_find_and_count_primes(void*);
int task_for_threads_to_check_primes(int);
void cleanup();

#endif  // MY_PRIME_COUNTER
