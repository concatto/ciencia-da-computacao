#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

struct problem {
  int* set;
  unsigned long int start;
  unsigned long int end; //Exclusive
};

struct solution {
  int* subset;
  int size;
};

void print_set(int* set, int size, FILE* out) {
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
int* generate_subset(int* set, unsigned long int elements, int* subset_size) {
  unsigned long int max_elements = (log(elements) / log(2)) + 1;
   
  int* subset = malloc(sizeof(int) * max_elements);

  int i;
  int current_index = 0;
  for (i = 0; i < max_elements; i++) {
    //If the bit on the i-th position is 1, then the number is added to the subset.
	unsigned long int val = (elements >> i) & 1;

    if (val == 1) {
      subset[current_index] = set[i];
      current_index++;
    }
  }

  print_set(subset, current_index, stdout);
  
  *subset_size = current_index;
  return subset;
}

//Calculates the sum of all the elements of a set.
//Complexity: O(n)
long int calculate_set_sum(int* set, int size) {
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
  struct problem* p = (struct problem*) data;

  unsigned long int i;
  for (i = p->start; i < p->end; i++) {
    int size;
	printf("i = %lu\n", i);
    int* subset = generate_subset(p->set, i, &size);
    
    long int sum = calculate_set_sum(subset, size);
    if (sum == 0) {
      struct solution* sol = malloc(sizeof(struct solution));
      sol->subset = subset;
      sol->size = size;

      return ((void*) sol);
    }
  }

  return NULL;
}

//Generates an array of random numbers with the specified amount of elements (inclusive).
//Complexity: O(n). The array might have repeated numbers.
int* generate_set(unsigned int set_size, int min, int max) {
  int i;
  int* set = malloc(sizeof(int) * set_size);

  for (i = 0; i < set_size; i++) {
    int value = min + (rand() % ((max + 1) - min));

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
  int min = set_size * -5;
  int max = set_size * 5;

  if (argc == 5) {
    min = atoi(argv[3]);
    max = atoi(argv[4]);
  }

  pthread_t threads[num_threads];
  
  int* set = generate_set(set_size, min, max);
  unsigned long int subset_count = pow(2, set_size) - 1; //Don't include the empty set
  unsigned long int work_per_thread = subset_count / num_threads;
  unsigned long int main_thread_work = subset_count - (work_per_thread * num_threads); //Fix rounding

  int i;

  struct problem problems[num_threads];
  for (i = 0; i < num_threads; i++) {
    struct problem p;
    p.set = set;
    p.start = 1 + (work_per_thread * i);
    p.end = ((i != num_threads - 1) ? (p.start + work_per_thread) : (subset_count));

    problems[i] = p;
  }

  //TODO: Begin work!

  int test_set[] = {1, 2, 3, -3, 6};
  struct problem p;
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

  return 0;
}
