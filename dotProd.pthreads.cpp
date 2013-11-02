#include <cstdio>
#include <pthread.h>

const int NUM_THREADS = 4;
const int N = 256;

// shared global variables
double a[N], b[N];
double local_sums[NUM_THREADS];


void *dotprod(void *arg)
{
    int thread_id = *((int*)arg);
    int my_first, my_last;
    double local_sum;

    my_first = thread_id * N / NUM_THREADS;
    my_last = (thread_id + 1) * N / NUM_THREADS;

    local_sum = 0.0;
    for (int i=my_first; i<my_last; i++) {
        local_sum = local_sum + a[i] * b[i];
    }

    local_sums[thread_id] = local_sum;
    pthread_exit((void *)0);
}


int main(int argc, char *argv[])
{
    int thread_ids[NUM_THREADS];
    double sum = 0.0;
    int status;

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    // initialize the a and b arrays
    for (int i=0; i<N; i++) {
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // spawn off the threads
    for (int i=0; i<NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], &attr, dotprod, &thread_ids[i]);
    }

    // join the threads
    for (int i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], (void **)&status);
        // local_sums[i] should be ready after thread[i] joins
        sum += local_sums[i];
    }

    pthread_attr_destroy(&attr);
    printf("sum = %g\n", sum);

    return 0;
}
