#include "MyPrimeCounter.h"

int main() {
    int how_much_threads = 0;
    int how_much_primes = 0;

    how_much_threads = 1000;

    create_list_of_primes_for_threads();
    how_much_primes = task_for_threads_to_check_primes(how_much_threads);

    printf("%d total primes.\n", how_much_primes);

    cleanup();
    return 0;
}
