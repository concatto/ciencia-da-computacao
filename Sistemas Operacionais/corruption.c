#include <stdio.h>
#include <pthread.h>

#define IT 1000000

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* do_work(void* arg) {
  int* x = (int*) arg;

  int i;
  for (i = 0; i < IT; i++) {
    pthread_mutex_lock(&lock);
    (*x)++;
    pthread_mutex_unlock(&lock);
  }

  return NULL;
}

int main(int argc, char** argv) {
  int x = 0;

  pthread_t tid;
  pthread_create(&tid, NULL, do_work, &x);

  int i;
  pthread_mutex_lock(&lock);
  for (i = 0; i < IT; i++) {
    x++;
  }
  pthread_mutex_unlock(&lock);

  pthread_join(tid, NULL);

  printf("Expected: %d.\n", IT * 2);
  printf("Result:   %d.\n", x);

  return 0;
}
