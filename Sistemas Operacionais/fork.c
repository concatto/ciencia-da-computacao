#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Starting\n");
  int test = 10;
  unsigned int* ptr = (unsigned int*) malloc(sizeof(unsigned int));
  *ptr = 15;

  int result = fork();
  printf("Forked: %d\n", result);

  printf("address: %p\n", ptr);
  printf("Hello, still alive!\n");
  printf("Will this be printed twice?\n");

  if (result == 0) {
    test = 30;
    *ptr = 40;
  } else {
    wait(NULL);
  }

  printf("Test is %d. Ptr is %d. I am %s\n", test, *ptr, result == 0 ? "child" : "parent");
  return 0;
}
