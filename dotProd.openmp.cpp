#include <cstdio>


int main(int argc, char *argv[])
{
    double sum;
    double a[256], b[256];
    int n = 256;

    // initialize the a and b arrays
    for (int i=0; i<n; i++) {
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }

    sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i=0; i<n; i++) {
        sum = sum + a[i] * b[i];
    }

    printf("sum = %g\n", sum);

    return 0;
}
