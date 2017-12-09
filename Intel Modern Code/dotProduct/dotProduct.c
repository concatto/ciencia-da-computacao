#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

double dotproduct(double *a, double *b, long long int N){
	long long int i;
	double dot = 0;

	//#pragma vector aligned
	//#pragma simd reduction(+ : dot)
	#pragma omp parallel for reduction(+ : dot)
	for(i = 0; i < N; i++)
		dot += a[i] * b[i];
			
	return dot;
}

int check (double r, long long int n){	
	return r == (double) 2 * n;
}

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };
	
	long long int i, n;
	double elapsed, start, end;
	double r;      

	if(argc != 2){
		fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoll(argv[1]);
	
	n = n % 8 == 0 ? n : n + (8 - n % 8);
	
	printf("number of elements: %lld\n", n);
	
	double *va = _mm_malloc(n * sizeof(double), 64);
	assert(va != NULL);
	
	double *vb = _mm_malloc(n * sizeof(double), 64);
	assert(vb != NULL);
	
	for(i = 0; i < n; i++){
		va[i] = 1; /* Do not */
		vb[i] = 2; /* change it */
	}
		
	start = omp_get_wtime();
	r = dotproduct(va, vb, n);
	end = omp_get_wtime();
	
	elapsed = end - start;
	
	printf("output is %lf, which is %s\ntime: %.3lf seconds\n", r, awnser[check(r, n)], elapsed);
	
	_mm_free(va);
	_mm_free(vb);

	return 0;
}
