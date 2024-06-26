


#include "MyPrimeCounter.h"

// Global variables
int array_size_of_primes = 0;
int *array_of_prime_numbers = NULL;
int *how_much_threads = NULL;
pthread_t *thread_list = NULL;

void cleanup() {
    free(array_of_prime_numbers);
    free(how_much_threads);
    free(thread_list);
}

bool check_if_number_is_prime_standard(int check_if_prime, int where_to_start) {
    int threshold = (int)sqrt(check_if_prime) + 1;
    for (int i = where_to_start; i <= threshold; i++) {
        if (check_if_prime % i == 0) {
            return false;
        }
    }
    return true;
}

void create_list_of_primes_for_threads() {
    int i, j;
    bool *list_of_status = (bool*)malloc(PRIMES_ARRAY_LIMIT * sizeof(bool));
    if (list_of_status == NULL) {
        perror("Failed to allocate memory for list_of_status");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < PRIMES_ARRAY_LIMIT; i++) {
        list_of_status[i] = true;
    }

    int threshold = (int)sqrt(PRIMES_ARRAY_LIMIT) + 1;
    for (i = 2; i < threshold; i++) {
        if (list_of_status[i]) {
            for (j = i * i; j < PRIMES_ARRAY_LIMIT; j += i) {
                list_of_status[j] = false;
            }
        }
    }

    int count = 0;
    for (i = 2; i < PRIMES_ARRAY_LIMIT; i++) {
        if (list_of_status[i]) {
            count++;
        }
    }

    array_of_prime_numbers = (int*)malloc(count * sizeof(int));
    if (array_of_prime_numbers == NULL) {
        perror("Failed to allocate memory for array_of_prime_numbers");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    for (i = 2; i < PRIMES_ARRAY_LIMIT; i++) {
        if (list_of_status[i]) {
            array_of_prime_numbers[index++] = i;
        }
    }
    array_size_of_primes = count;
    free(list_of_status);
}
bool isPrime(int a_number) {
    for (int i = 0; i < array_size_of_primes; i++) {
        if (a_number % array_of_prime_numbers[i] == 0) {
            return false;
        }
    }
    return check_if_number_is_prime_standard(a_number, array_of_prime_numbers[array_size_of_primes - 1] + 1);
}

int count_how_many_primes_were() {
    int curr_number_scanned;
    int how_much_primes = 0;

    while (scanf("%d", &curr_number_scanned) != EOF) {
        if (isPrime(curr_number_scanned)) {
            how_much_primes++;
        }
    }
    return how_much_primes;
}

void* thread_task_for_find_and_count_primes(void *arguments) {
    int *workerCounter = (int*)arguments;
    *workerCounter = count_how_many_primes_were();
    return NULL;
}

int task_for_threads_to_check_primes(int threads) {
    int total_primes = 0;

    how_much_threads = (int*)malloc(threads * sizeof(int));
    thread_list = (pthread_t*)malloc(threads * sizeof(pthread_t));

    if (how_much_threads == NULL || thread_list == NULL) {
        perror("Failed to allocate memory for threads");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < threads; i++) {
        how_much_threads[i] = 0;
        pthread_create(&thread_list[i], NULL, thread_task_for_find_and_count_primes, &how_much_threads[i]);
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(thread_list[i], NULL);
    }

    for (int i = 0; i < threads; i++) {
        total_primes += how_much_threads[i];
    }

    return total_primes;
}