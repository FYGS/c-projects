#include <pthread.h>
#include <stdio.h>

/* Calcules des nombres premiers successifs (très inefficace). Renvoie 4 le Nième nombre premier où N est la valeur pointée par *ARG. */
void *compute_prime(void *arg)
{
  int candidate = 2;
  int n = *((int *)arg);
  while (1)
  {
    int factor;
    int is_prime = 1;

    /* Teste si le nombre est premier par divisions successives. */
    for (factor = 2; factor < candidate; ++factor)
      if (candidate % factor == 0)
      {
        is_prime = 0;
        break;
      }
    /* Est-ce le nombre premier que nous cherchons ? */
    if (is_prime)
    {
      if (--n == 0)
        /* Renvoie le nombre premier désiré via la valeur de retour du thread. */
        return (void *)candidate;
    }
    ++candidate;
  }
  return NULL;
}

int main()
{
  pthread_t thread;
  int which_prime = 5000;
  int prime;
  /* Démarre le thread de calcul jusqu’au 5 000ème nombre premier. */
  pthread_create(&thread, NULL, &compute_prime, &which_prime);
  /* Faire autre chose ici... */
  /* Attend la fin du thread de calcul et récupère le résultat. */
  pthread_join(thread, (void *)&prime);
  /* Affiche le nombre premier calculé. */
  printf("Le %dème nombre premier est %d.\n", which_prime, prime);
  return 0;
}