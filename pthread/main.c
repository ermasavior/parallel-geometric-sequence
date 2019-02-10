#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int thread_count;
int flag;
long n;
double a, r;
double sum = 0;

void *geometricSum(void* rank);

int main(int argc, char* argv[]) {
    long        thread;
    pthread_t*  thread_handles;
	double time_spent = 0.0;

	clock_t begin = clock();

    // ./main <thread_count> <a> <r> <n>
    thread_count = strtol(argv[1], NULL, 10);
    a = strtol(argv[2], NULL, 10);
    r = strtol(argv[3], NULL, 10);
    n = strtol(argv[4], NULL, 10);

    flag = 0;

    thread_handles = malloc(thread_count*sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL,
                        geometricSum, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }
    free(thread_handles);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("a = %.2lf, r = %.2lf, n = %ld\n", a, r, n);
    printf("Sn = %.2lf\n", sum);
    printf("Time elapsed is %f seconds\n", time_spent);
    return 0;
}

void *geometricSum(void* rank) {
    long my_rank = (long) rank;
    double my_sum = 0;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i;

    if (n % thread_count != 0 && my_rank == thread_count-1)
        my_last_i = n;
    else
        my_last_i = my_first_i + my_n;

    for (i = my_first_i; i < my_last_i; i++) {
        my_sum += a * pow(r, i);
    }

    while (flag != my_rank);
    sum += my_sum;
    flag = (flag+1) % thread_count;
    // printf("%ld Sn_local = %.2lf\n", my_rank, my_sum);

    return NULL;
}