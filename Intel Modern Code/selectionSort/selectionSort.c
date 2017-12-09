#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <omp.h>

void selection_sort(int *v, int n){
	int i, j, min, tmp, global_min;
	for(i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");

	for(i = 0; i < n - 1; i++){
		#pragma omp parallel private(min)
		{
			min = i;

			#pragma omp single
			global_min = min;

			#pragma omp for
			for(j = i + 1; j < n; j++) {
				printf("Thread %d is looking at %d\n", omp_get_thread_num(), v[j]);
				if(v[j] < v[min])
					min = j;
			}

			printf("Min for thread %d: %d\n", omp_get_thread_num(), v[min]);

			#pragma omp critical
			{
				if (v[min] < v[global_min]) {
					global_min = min;
				}
			}
		}

		printf("Global min elected as %d\n", v[global_min]);

		tmp = v[i];
		v[i] = v[global_min];
		v[global_min] = tmp;
	}
}

int compare (const void * a, const void * b){
  return (* (int*) a - * (int*) b); /* Do not change it! */
}

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };
	int *vector, *test;
	int i, n, is_ok;
	double elapsed, start, end;

	if(argc != 2){
		fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);

	printf("number of elements: %d\n", n);

	vector = (int *) malloc(n * sizeof(int));
	assert(vector != NULL);

	test = (int *) malloc(n * sizeof(int));
	assert(test != NULL);

	srand(time(NULL));

	for(i = 0; i < n; i++) {
		vector[i] = rand() % 500;
	}

	memcpy(test, vector, n * sizeof(int));

	qsort (test, n, sizeof(int), compare);

	start = omp_get_wtime();
	selection_sort(vector, n);
	end = omp_get_wtime();

	elapsed = end - start;

	is_ok = (memcmp(vector, test, n * sizeof(int)) == 0);

	printf("sorted values are %s\ntime: %.3f seconds\n", awnser[is_ok], elapsed);

	free(vector);
	free(test);

	return 0;
}
