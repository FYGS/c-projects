#include <malloc.h>

struct job
{
  /* Champ de chaînage. */
  struct job *next;
  /* Autres champs décrivant la tâche... */
};
/* Liste chaînée de tâches en attente. */
struct job *job_queue;
/* Traite les tâches jusqu’à ce que la file soit vide. */
void *thread_function(void *arg)
{
  while (job_queue != NULL)
  {
    /* Récupère la tâche suivante. */
    struct job *next_job = job_queue;
    /* Supprime cette tâche de la liste. */
    job_queue = job_queue->next;
    /* Traite la tâche. */
    process_job(next_job);
    /* Libération des ressources. */
    free(next_job);
  }
  return NULL;
}