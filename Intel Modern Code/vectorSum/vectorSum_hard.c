#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i, sum = 0, local_sum, work;
	int thread_id, n_threads, start, end;
	
	#pragma omp parallel private(i, thread_id, local_sum, start, end)
	{
		local_sum = 0;
		thread_id = omp_get_thread_num();

		#pragma omp single
		{
			n_threads = omp_get_num_threads();
			work = N / n_threads;
		}

		start = work * thread_id;
		end = (thread_id < n_threads - 1) ? (start + work) : N;
		// Se for a última, trabalha até o fim


		printf("in thread %d of %d from %d to %d\n", thread_id, n_threads, start, end);

		for(i = start; i < end; i++){
			local_sum += v[i];

			//#pragma omp atomic
			//sum += v[i];
		}

		#pragma omp atomic
		sum += local_sum;
	}

	return sum;
}

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };

	long long int i, vsum, n;
	int *v;
	double elapsed, start, end;

	if(argc != 2){
		fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoll(argv[1]);
	printf("number of elements: %lld\n", n);

	v = (int *) malloc(n * sizeof(int));
	assert(v != NULL);

	for(i = 0; i < n; i++)
		v[i] = 1; /* Do not change it! */

	start = omp_get_wtime();
	vsum = sum(v, n);
	end = omp_get_wtime();

	elapsed = end - start;

	printf("sum value is %s\ntime: %.3f seconds\n", awnser[vsum == n], elapsed);

	free(v);

	return 0;
}
