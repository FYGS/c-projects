#include <malloc.h>
#include <pthread.h>

struct job
{
  /* Pointeur vers la tâche suivante. */
  struct job *next;
};
/* Liste chaînée des tâches en attente. */
struct job *job_queue;
/* Mutex protégeant la file de tâches. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
/* Traite les tâches en attente jusqu’à ce que la file soit vide. */
void *thread_function(void *arg)
{
  while (1)
  {
    struct job *next_job;
    /* Verrouille le mutex de la file de tâches. */
    pthread_mutex_lock(&job_queue_mutex);
    /* Il est maintenant sans danger de vérifier si la file est vide. */
    if (job_queue == NULL)
      next_job = NULL;
    else
    {
      /* Récupère la tâche suivante. */
      next_job = job_queue;
      /* Supprime cette tâche de la liste. */
      job_queue = job_queue->next;
    }
    /* Déverrouille le mutex de la file de tâches car nous en avons fini avec la file pour l’instant. */
    pthread_mutex_unlock(&job_queue_mutex);
    /* La file était vide ? Si c’est la cas, le thread se termine. */
    if (next_job == NULL)
      break;
    /* Traite la tâche. */
    process_job(next_job);
    /* Libération des ressources. */
    free(next_job);
  }
  return NULL;
}