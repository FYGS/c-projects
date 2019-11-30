#include <pthread.h>
#include <stdio.h>

/* Affiche des x sur stderr. Paramètre inutilisé. Ne finit jamais. */
void *print_xs(void *unused)
{
  while (1)
    fputc('x', stderr);
  return NULL;
}
/* Le programme principal. */
int main()
{
  pthread_t thread_id;
  /* Crée un nouveau thread. Le nouveau thread exécutera la fonction
    print_xs. */
  pthread_create(&thread_id, NULL, &print_xs, NULL);
  /* Affiche des o en continue sur stderr. */
  while (1)
    fputc('o', stderr);
  return 0;
}