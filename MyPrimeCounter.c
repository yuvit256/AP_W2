#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <math.h>

typedef struct
{
    int *numbers;
    int start;
    int end;
    int primeCount;
} ThreadData;
bool isPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    if (n <= 3)
    {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    int sqrt_n = sqrt(n);
    for (int i = 5; i <= sqrt_n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}


//the is prime function that provided

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

atomic_int totalPrimes = 0;

void *countPrimes(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int count = 0;
    for (int i = data->start; i < data->end; i++)
    {
        if (isPrime(data->numbers[i]))
        {
            count++;
        }
    }
    atomic_fetch_add(&totalPrimes, count);
    pthread_exit(NULL);
}

int main()
{
    int optimal_threads = 6; // Fixed number of threads (adjust as needed)
    int *numbers = NULL;
    int num, count = 0, capacity = 45830;

    numbers = (int *)malloc(capacity * sizeof(int));

    while (scanf("%d", &num) != EOF)
    {
        if (count == capacity)
        {
            capacity *= 2;
            numbers = (int *)realloc(numbers, capacity * sizeof(int));
            if (numbers == NULL)
            {
                perror("Memory allocation failed");
                exit(1);
            }
        }
        numbers[count++] = num;
    }

    pthread_t threads[optimal_threads];
    ThreadData threadData[optimal_threads];
    int chunkSize = (count + optimal_threads - 1) / optimal_threads;

    for (int i = 0; i < optimal_threads; i++)
    {
        threadData[i].numbers = numbers;
        threadData[i].start = i * chunkSize;
        threadData[i].end = (i == optimal_threads - 1) ? count : (i + 1) * chunkSize;
        pthread_create(&threads[i], NULL, countPrimes, &threadData[i]);
    }

    for (int i = 0; i < optimal_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("%d total primes.\n", totalPrimes);

    free(numbers);

    return 0;
}


