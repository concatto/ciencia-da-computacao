#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>
#include <stddef.h>
#include "pcg_basic.h"

#define DEBUG 0
int G_CHUNK_SIZE = 1000;

typedef long long int large_int;
typedef unsigned long long int large_uint;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
large_uint G_current_start;
large_uint G_subset_count;
int G_terminated_flag = 0;
large_uint G_steps = 0;

void increment_step() {
	pthread_mutex_lock(&mutex);
	G_steps++;
	pthread_mutex_unlock(&mutex);
}

struct solution {
  large_int* subset;
  int size;
};

large_uint get_next_start() {
	pthread_mutex_lock(&mutex);
	
	large_uint start = G_current_start;
	G_current_start = start + G_CHUNK_SIZE;
	
	pthread_mutex_unlock(&mutex);
	
	return start;
}

void print_set(large_int* set, int size, FILE* out) {
  int i;
  fprintf(out, "{");
  for (i = 0; i < size; i++) {
    if (i > 0) {
      fprintf(out, ", ");
    }
    
    fprintf(out, "%lld", set[i]);
  }

  fprintf(out, "}\n");
}

//Generates a subset from the binary representation of a value.
//Complexity: O(n)
large_int* generate_subset(large_int* set, large_uint elements, int* subset_size) {
  large_uint max_elements = (log(elements) / log(2)) + 1;
   
  large_int* subset = malloc(sizeof(large_int) * max_elements);

  int i;
  int current_index = 0;
  for (i = 0; i < max_elements; i++) {
    //If the bit on the i-th position is 1, then the number is added to the subset.
	large_uint val = (elements >> i) & 1;
	//printf("%lu", val);

    if (val == 1) {
      subset[current_index] = set[i];
      current_index++;
    }
  }

  //printf("\n");
  //print_set(subset, current_index, stdout);
  
  *subset_size = current_index;
  return subset;
}

//Calculates the sum of all the elements of a set.
//Complexity: O(n)
large_int calculate_set_sum(large_int* set, int size) {
  large_int sum = 0;
  int i;
  for (i = 0; i < size; i++) {
    sum += set[i];
  }

  return sum;
}

//Tries to find a subset whose sum is 0.
//Complexity: O(n^2).
void* find_zero_subset(void* data) {
  large_int* set = (large_int*) data;

  while (1) { 
	  //Acquire work
	  large_uint start = get_next_start();
	  large_uint i;
	  
	  //Do work
	  for (i = start; i < start + G_CHUNK_SIZE; i++) {
		if (i >= G_subset_count || G_terminated_flag == 1) {
			return NULL;
		}
		  
		int size;
		large_int* subset = generate_subset(set, i, &size);
		
		large_int sum = calculate_set_sum(subset, size);
		//increment_step();
		if (sum == 0) {
		  struct solution* sol = (struct solution*) malloc(sizeof(struct solution));
		  sol->subset = subset;
		  sol->size = size;

		  printf("Solution found!\n");
		  
		  pthread_mutex_lock(&mutex);
		  G_terminated_flag = 1;
		  pthread_mutex_unlock(&mutex);
		  
		  return ((void*) sol);
		}
		
		free(subset);
	  }
  }

  return NULL;
}

//Generates an array of random numbers with the specified amount of elements (inclusive).
//Complexity: O(n). The array might have repeated numbers.
large_int* generate_set(unsigned int set_size, large_int range) {
  int i;
  large_int* set = malloc(sizeof(large_int) * set_size);

  for (i = 0; i < set_size; i++) {
	double val = (((double) pcg32_boundedrand(range)) / (range / 2.0)) - 1;
	printf("%.5f\n", val);
    large_int value = val * range;

    set[i] = value;
  }

  return set;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "Not enough arguments.\n");
    fprintf(stderr, "Usage: setsum <thread count> <set size>\n");
    return EXIT_FAILURE;
  }

  int rounds = atoi(argv[0]);
  pcg32_srandom(time(NULL), (intptr_t) &rounds);
  
  int num_threads = atoi(argv[1]);
  int set_size = atoi(argv[2]);
  large_int range = pow(2, set_size / 2);

  pthread_t threads[num_threads];
  
  if (DEBUG) {
	set_size = 7;
  }
  
  clock_t start = clock();
  
  large_int* set = generate_set(set_size, range);
  print_set(set, set_size, stdout);
  
  G_subset_count = pow(2, set_size);
  G_current_start = 1;
  
  int i;
  for (i = 0; i < num_threads; i++) {
	pthread_create(&threads[i], NULL, find_zero_subset, (void*) set);
  }
  
  struct solution* sol = NULL;
  for (i = 0; i < num_threads; i++) {
	void* ret;
	pthread_join(threads[i], &ret);
	
	if (ret != NULL) {
		printf("Thread %d found a solution!\n", i);
		sol = ret;
	} else {
		printf("Thread %d was not able to find a solution.\n", i);
	}
  }
  
  clock_t end = clock();
  printf("%.4f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
  
  printf("Joined with result %x and %d executions\n", sol, G_steps);
  if (sol != NULL) {
	print_set(sol->subset, sol->size, stdout);
  }

  return 0;
}