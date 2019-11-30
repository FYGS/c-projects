#include <stdio.h>

 /* La variable ENVIRON contient l’environnement. Il est terminé par NULL.*/
extern char** environ;

int main() {
  char** var;

  for (var = environ; *var != NULL; ++var)
  {
    printf("%s\n", *var);
  }
  
  return 0;
}