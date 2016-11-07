#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>
#include <stddef.h>
#include "pcg_basic.h"

#define DEBUG 0

typedef long long int large_int;
typedef unsigned long long int large_uint;

large_uint G_subset_count;

struct solution {
  large_int* subset;
  int size;
};

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
  large_uint max_elements = round(log(elements) / log(2)) + 1;
   
  large_int* subset = malloc(sizeof(large_int) * max_elements);

  int i;
  int current_index = 0;
  for (i = 0; i < max_elements; i++) {
    //If the bit on the i-th position is 1, then the number is added to the subset.
		large_uint val = (elements >> i) & 1;

    if (val == 1) {
      subset[current_index] = set[i];
      current_index++;
    }
  }
  
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

	int i;
	for (i = 1; i < G_subset_count; i++) {
		int size;
		large_int* subset = generate_subset(set, i, &size);			
		large_int sum = calculate_set_sum(subset, size);

		if (sum == 0) {
			struct solution* sol = (struct solution*) malloc(sizeof(struct solution));
			sol->subset = subset;
			sol->size = size;

			printf("Solution found!\n");
			
			return ((void*) sol);
		}
		
		free(subset);
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
    large_int value = val * range;

    set[i] = value;
  }

  return set;
}

void test_single(FILE* file, int set_size, large_int range) {	
	clock_t start = clock();
	
	large_int* set = generate_set(set_size, range);
	G_subset_count = round(pow(2, set_size));
	
	struct solution* sol = find_zero_subset((void*) set);
	if (sol != NULL) {
		print_set(sol->subset, sol->size, stdout);
		free(sol);
	}
	
	clock_t end = clock();
	double delta = (((double) (end - start)) / CLOCKS_PER_SEC);
	
	fprintf(file, "1,%d,%.6f\n", set_size, delta);
	fflush(file);
}

int main(int argc, char** argv) {
  /*
  if (argc < 3) {
    fprintf(stderr, "Not enough arguments.\n");
    fprintf(stderr, "Usage: setsum <thread count> <set size>\n");
    return EXIT_FAILURE;
  }
  */

	unsigned int seed = 1478456124;
  
	FILE* file = fopen("out_single_seeded_final.csv", "w");
	
	fprintf(file, "threads,setsize,time\n");
	
  int k, it;
	pcg32_srandom(seed, 54u);
	
	for (k = 0; k < 13; k++) {
		for (it = 0; it < 30; it++) {

			int set_size = (k + 1) * 4;
			large_int range = round(pow(2, set_size / 2));
			
			printf("k = %d, it = %d\n", k, it);

			test_single(file, set_size, range);
		}
	}

  return 0;
}