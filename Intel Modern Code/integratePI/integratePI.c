#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double integrate_pi(long long int N){
	int i;
	double x, sum = 0.0;
	double step = 1.0 / (double) N;

	for(i = 1; i <= N; i++){
		x = ((double) i - 0.5) * step;
		sum = sum + 4.0 / (1.0 + x * x);
	}

	return step * sum;
}

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };

	double pi;
	long long int n;
	double elapsed, start, end;

	if(argc != 2){
		fprintf(stderr, "Usage: %s <number of rectangles>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoll(argv[1]);
	printf("number of rectangles: %lld\n", n);

	start = omp_get_wtime();
	pi = integrate_pi(n);
	end = omp_get_wtime();

	elapsed = end - start;

	printf("pi value is %lf\ntime: %.3f seconds\n", pi, elapsed);

	return 0;
}