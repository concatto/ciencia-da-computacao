#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>

int main(int argc, char **argv){
    int n, steps;
    double elapsed, start, end;

    if(argc != 3){
        fprintf(stderr, "Usage: %s <size> <steps>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);
    steps = atoi(argv[2]);

    const float pi  = 2.0f * asinf(1.0f);
    const float tol = 1.0e-5f;
    float error     = 1.0f;

    float *A = (float *) calloc(n * n, sizeof(float));
    float *Anew = (float *) malloc(n * n * sizeof(float));
    float *y0 = (float *) malloc(n * sizeof(float));

    int i, j, step;

    // set boundary conditions
    for (i = 0; i < n; i++){
        A[i]   = 0.f;
        A[(n - 1) * n + i] = 0.f;
    }
    
    for (j = 0; j < n; j++){
        y0[j] = sinf(pi * j / (n - 1));
        A[j * n] = y0[j];
        A[j * n + n - 1] = y0[j] * expf(-pi);
    }

    for (i = 1; i < n; i++){
       Anew[i]   = 0.f;
       Anew[(n - 1) * n + i] = 0.f;
    }
    for (j = 1; j < n; j++){
        Anew[j * n]   = y0[j];
        Anew[j * n + n - 1] = y0[j] * expf(-pi);
    }    

    printf("Jacobi relaxation calculation: %d x %d mesh\n", n, n);

    start = omp_get_wtime();
    for(step = 1; step <= steps; step++){

        for(j = 1; j < n - 1; j++)
            for(i = 1; i < n - 1; i++)
                Anew[j * n + i] = 0.25f * (A[j * (i + 1)] + A[j * (i - 1)] + A[(j - 1) * i] + A[(j + 1) * i]);

        if(step == steps)
            break;

        for(j = 1; j < n - 1; j++)
            for(i = 1; i < n - 1; i++)
                A[j * n + i] = Anew[j * n + i];
    }
    end = omp_get_wtime();
    
    elapsed = end - start;

    error = 0.f;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            error += fabsf(Anew[i * n + j] - A[i * n + j]);
    
    printf("output is %lf\ntime: %.3lf seconds\n", error, elapsed);

    free(A);
    free(Anew);
    free(y0);
}