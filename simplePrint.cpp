#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int n = 10;
    int i;

    #pragma omp parallel shared(n) private(i)
    {
        #pragma omp for
        for (i=0; i<n; i++) {
            int threadID = omp_get_thread_num();
            printf("Thread %d executing loop iteration %d\n", threadID, i);
        }
    }

    return 0;
}
