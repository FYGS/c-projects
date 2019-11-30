#include <stdio.h>
#include <unistd.h>

int main () {
  printf ("L’identifiant du processus est %d\n", (int) getpid ());
  printf ("L’identifiant du processus parent est %d\n", (int) getppid ());
  return 0;
} 