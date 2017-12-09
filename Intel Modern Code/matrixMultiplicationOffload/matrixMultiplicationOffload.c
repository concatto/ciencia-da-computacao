#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

void matrix_mult(double *A, double *B, double *C, int N){
	int i, j, k;

	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			for(k = 0; k < N; k++)
				C[i * N + j] += A[i * N + k] * B[k * N + j];

}

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };
	
	int i, j, n, is_ok;
	double elapsed, start, end;
	
	if(argc != 2){
		fprintf(stderr, "Usage: %s <size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	
	n = n % 8 == 0 ? n : n + (8 - n % 8);
	
	printf("number of rows x cols: %i\n", n);
	
	double *A = _mm_malloc(n * n * sizeof(double), 64);
	assert(A != NULL);
	
	double *B = _mm_malloc(n * n * sizeof(double), 64);
	assert(B != NULL);
	
	double *C = _mm_malloc(n * n * sizeof(double), 64);
	assert(C != NULL);
	
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++){
			A[i * n + j] = 1; /* Do not */
			B[i * n + j] = 1; /* change */
			C[i * n + j] = 0; /* it */
		}
	
	start = omp_get_wtime();
	matrix_mult(A, B, C, n);
	end = omp_get_wtime();
	
	elapsed = end - start;

	is_ok = 1;	
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(C[i * n + j] != (double) n){
				is_ok = 0;
				i = n;
				j = n;
			}
	
	printf("multiply values are %s\ntime: %.3f seconds\n", awnser[is_ok], elapsed);
	
	_mm_free(A);
	_mm_free(B);
	_mm_free(C);

	return 0;
}