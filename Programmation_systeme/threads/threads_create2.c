#include <pthread.h>
#include <stdio.h>

/* Paramètres de la fonction print. */
struct char_print_parms
{
  /* Caractère à afficher. */
  char character;
  /* Nombre de fois où il doit être affiché. */
  int count;
};
/* Affiche un certain nombre de caractères sur stderr, selon le contenu de PARAMETERS, qui est un pointeur vers une struct char_print_parms. */
void *char_print(void *parameters)
{
  /* Effectue un transtypage du pointeur void vers le bon type. */
  struct char_print_parms *p = (struct char_print_parms *)parameters;
  int i;
  for (i = 0; i < p->count; ++i)
    fputc(p->character, stderr);
  return NULL;
}

/* Programme principal. */
int main()
{
  pthread_t thread1_id;
  pthread_t thread2_id;
  struct char_print_parms thread1_args;
  struct char_print_parms thread2_args;
  /* Crée un nouveau thread affichant 30 000 x. */
  thread1_args.character = 'x';
  thread1_args.count = 30000;
  pthread_create(&thread1_id, NULL, &char_print, &thread1_args);
  /* Crée un nouveau thread affichant 20 000 'o'. */
  thread2_args.character = 'o';
  thread2_args.count = 20000;
  pthread_create(&thread2_id, NULL, &char_print, &thread2_args);

  /* S’assure que le premier thread est terminé. */
  pthread_join (thread1_id, NULL);
  /* S’assure que le second thread est terminé. */
  pthread_join (thread2_id, NULL); 

  printf("\n\n\nFin de programme !\n");
  return 0;
}