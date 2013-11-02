#include <stdio.h>
#include <stdlib.h>


void mxvSeq(int m, int n, double * restrict a,
        double * restrict b, double * restrict c)
{
    int i, j;

    for (i=0; i<m; i++) {
        a[i] = 0.0;
        for (j=0; j<n; j++) {
            a[i] += b[i*n+j] * c[j];
        }
    }
}


void mxvOpenMP(int m, int n, double * restrict a,
        double * restrict b, double * restrict c)
{
    int i, j;

    #pragma omp parallel for default(none) shared(m,n,a,b,c) private(i,j)
    for (i=0; i<m; i++) {
        a[i] = 0.0;
        for (j=0; j<n; j++) {
            a[i] += b[i*n+j] * c[j];
        }
    }
}


int main(int argc, char *argv[])
{
    double *a, *b, *c;

    int i, j;
    int m, n;

    if (argc < 3) {
        printf("Please enter m and n: ");
        scanf("%d %d", &m, &n);
    } else {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
    }

    a = (double *)malloc(m * sizeof(double));
    if (a == NULL) {
        perror("memory allocation for a");
    }
    b = (double *)malloc(m * n * sizeof(double));
    if (b == NULL) {
        perror("memory allocation for b");
    }
    c = (double *)malloc(n * sizeof(double));
    if (c == NULL) {
        perror("memory allocation for c");
    }


    printf("Initializing matrix B and vector C\n");
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            b[i*n+j] = 1.0;
        }
    }
    for (j=0; j<n; j++) {
        c[j] = 2.0;
    }


    printf("Executing mxv function for m=%d, n=%d\n", m, n);
    //mxvSeq(m, n, a, b, c);
    mxvOpenMP(m, n, a, b, c);

    //for (i=0; i<m; i++) {
    //    printf("%7.2g  ", a[i]);
    //}
    //printf("\n");

    free(a);
    free(b);
    free(c);

    return 0;
}
