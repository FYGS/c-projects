#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

/* Clé utilisée pour associer un pointeur de fichier à chaque thread. */
static pthread_key_t thread_log_key;
/* Écrit MESSAGE vers le fichier journal du thread courant. */
void write_to_thread_log(const char *message)
{
  FILE *thread_log = (FILE *)pthread_getspecific(thread_log_key);
  fprintf(thread_log, "%s\n", message);
}
/* Ferme le pointeur vers le fichier journal THREAD_LOG. */
void close_thread_log(void *thread_log)
{
  fclose((FILE *)thread_log);
}
void *thread_function(void *args)
{
  char thread_log_filename[20];
  FILE *thread_log;
  /* Génère le nom de fichier pour le fichier journal de ce thread. */
  sprintf(thread_log_filename, "thread%d.log", (int)pthread_self());
  /* Ouvre le fichier journal. */
  thread_log = fopen(thread_log_filename, "w");
  /* Stocke le pointeur de fichier dans les données propres au thread sous la clé thread_log_key. */
  pthread_setspecific(thread_log_key, thread_log);
  write_to_thread_log("Démarrage du Thread.");
  /* Placer les traitements ici... */
  return NULL;
}
int main()
{
  int i;
  pthread_t threads[5];
  /* Crée une clé pour associer les pointeurs de fichier journal dans les données propres au thread. Utilise close_thread_log pour libérer les pointeurs de fichiers. */
  pthread_key_create(&thread_log_key, close_thread_log);
  /* Crée des threads pour effectuer les traitements. */
  for (i = 0; i < 5; ++i)
    pthread_create(&(threads[i]), NULL, thread_function, NULL);
  /* Attend la fin de tous les threads. */
  for (i = 0; i < 5; ++i)
    pthread_join(threads[i], NULL);
  return 0;
}