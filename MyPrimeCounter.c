#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <math.h>

typedef struct
{
    int totalPrimes;
    pthread_mutex_t prime_lock;
} ThreadData;

bool isPrime(int n) {
  if (n <= 2 || n % 2 == 0) 
    return n == 2;
  for (int i = 3; i * i <= n; i += 2)
    if (n % i == 0)
      return false;
  return true;
}


// the is prime function that provided

// bool isPrime(int n)
// {
//     if (n <= 1)
//     {
//         return false;
//     }
//     for (int i = 2; i * i <= n; i++)
//     {
//         if (n % i == 0)
//         {
//             return false;
//         }
//     }
//     return true;
// }

void *countPrimes(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int num = 0;
    while (scanf("%d", &num) != EOF)
    {
        if (isPrime(num))
        {
            pthread_mutex_lock(&data->prime_lock);
            data->totalPrimes++;
            pthread_mutex_unlock(&data->prime_lock);
        }
    }
    pthread_exit(NULL);
}

int main()
{
    int optimal_threads = 6; // Fixed number of threads (adjust as needed)
    pthread_t threads[optimal_threads];
    ThreadData threadData;
    threadData.totalPrimes = 0;
    pthread_mutex_init(&threadData.prime_lock, NULL);

    for (int i = 0; i < optimal_threads; i++)
    {
        pthread_create(&threads[i], NULL, countPrimes, &threadData);
    }

    for (int i = 0; i < optimal_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("%d total primes.\n", threadData.totalPrimes);

    pthread_mutex_destroy(&threadData.prime_lock);

    return 0;
}
