#include <stdio.h>
#include <omp.h>

/*
Distribuição cíclica (visitar todas as posições
de um array de tamanho N
for (i = thread_id; i < N; i += num_threads)
*/

int main(){
	int myid, nthreads;
	
	// Declarações internas são private sempre.
	// Declarações shared (padrão) precisam estar fora.
	#pragma omp parallel private(myid) shared(nthreads)
	{
		myid = omp_get_thread_num();

		#pragma omp single
		nthreads = omp_get_num_threads();

		printf("%d of %d - hello world!\n", myid, nthreads);
	}

	return 0;
}
