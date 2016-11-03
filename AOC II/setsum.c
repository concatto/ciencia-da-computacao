#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0
#define CHUNK_SIZE 1000

typedef unsigned long int bigint;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bigint G_current_start;
bigint G_subset_count;
int G_terminated_flag = 0;
bigint G_steps = 0;

void increment_step() {
	pthread_mutex_lock(&mutex);
	G_steps++;
	pthread_mutex_unlock(&mutex);
}

struct solution {
  long int* subset;
  int size;
};

bigint get_next_start() {
	pthread_mutex_lock(&mutex);
	
	bigint start = G_current_start;
	G_current_start = start + CHUNK_SIZE;
	
	pthread_mutex_unlock(&mutex);
	
	return start;
}

void print_set(long int* set, int size, FILE* out) {
  printf("Size is %d\n", size);
	
  int i;
  fprintf(out, "{");
  for (i = 0; i < size; i++) {
    if (i > 0) {
      fprintf(out, ", ");
    }
    
    fprintf(out, "%d", set[i]);
  }

  fprintf(out, "}\n");
}

//Generates a subset from the binary representation of a value.
//Complexity: O(n)
long int* generate_subset(long int* set, bigint elements, int* subset_size) {
  bigint max_elements = (log(elements) / log(2)) + 1;
   
  long int* subset = malloc(sizeof(long int) * max_elements);

  int i;
  int current_index = 0;
  for (i = 0; i < max_elements; i++) {
    //If the bit on the i-th position is 1, then the number is added to the subset.
	bigint val = (elements >> i) & 1;
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
long int calculate_set_sum(long int* set, int size) {
  long int sum = 0;
  int i;
  for (i = 0; i < size; i++) {
    sum += set[i];
  }

  return sum;
}

//Tries to find a subset whose sum is 0.
//Complexity: O(n^2).
void* find_zero_subset(void* data) {
  long int* set = (long int*) data;

  while (1) { 
	  //Acquire work
	  bigint start = get_next_start();
	  bigint i;
	  
	  //Do work
	  for (i = start; i < start + CHUNK_SIZE; i++) {
		if (i >= G_subset_count || G_terminated_flag == 1) {
			return NULL;
		}
		  
		int size;
		long int* subset = generate_subset(set, i, &size);
		
		long int sum = calculate_set_sum(subset, size);
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
long int* generate_set(unsigned int set_size, long int min, long int max) {
  int i;
  long int* set = malloc(sizeof(long int) * set_size);

  for (i = 0; i < set_size; i++) {
	double val = rand() / ((double) RAND_MAX);
    int value = val * (max - min + 1) + min;

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

  srand(time(NULL));
  
  int num_threads = atoi(argv[1]);
  int set_size = atoi(argv[2]);
  long long int max = pow(2, set_size) / 2;
  long long int min = -max;
  
  if (argc == 5) {
    min = atoi(argv[3]);
    max = atoi(argv[4]);
  }

  pthread_t threads[num_threads];
  
  if (DEBUG) {
	set_size = 7;
  }
  
  clock_t start = clock();
  
  long int* set = generate_set(set_size, min, max);
  print_set(set, set_size, stdout);
  
  
  if (DEBUG) {
	set[0] = 1;
	set[1] = 2;
	set[2] = 4;
	set[3] = -90;
	set[4] = 6;
	set[5] = 7;
	set[6] = -12;
  }
  
  G_subset_count = pow(2, set_size);
  G_current_start = 1;
  
  //unsigned long int work_per_thread = subset_count / num_threads;
  //unsigned long int main_thread_work = subset_count - (work_per_thread * num_threads); //Fix rounding

  
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
  fprintf(stdout, "%.4f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
  
  fprintf(stdout, "Joined with result %x and %d executions\n", sol, G_steps);
  if (sol != NULL) {
	print_set(sol->subset, sol->size, stdout);
  }

  /*struct problem problems[num_threads];
  for (i = 0; i < num_threads; i++) {
    struct problem p;
    p.set = set;
    p.start = 1 + (work_per_thread * i);
    p.end = ((i != num_threads - 1) ? (p.start + work_per_thread) : (subset_count));

    problems[i] = p;
  }*/

  //TODO: Begin work!

  
  /*struct problem p;
  p.set = test_set;
  p.start = 1;
  p.end = pow(2, 5);

  void* result = find_zero_subset((void*) &p);
  if (result != NULL) {
    struct solution* sol = (struct solution*) result;
    fprintf(stdout, "Found!\n");
    print_set(sol->subset, sol->size, stdout);
  } else {
    fprintf(stdout, "No solution found.\n");
  }
  */

  return 0;
}