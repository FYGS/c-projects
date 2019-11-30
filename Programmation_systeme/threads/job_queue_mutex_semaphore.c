#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>

struct job
{
  /* Champ de chaînage. */
  struct job *next;
  /* Autres champs décrivant la tâche... */
};
/* Liste chaînée des tâches en attente. */
struct job *job_queue;
/* Mutex protégeant job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
/* Sémaphore comptant le nombre de tâches dans la file. */
sem_t job_queue_count;
/* Initialisation de la file de tâches. */
void initialize_job_queue()
{
  /* La file est initialement vide. */
  job_queue = NULL;
  /* Initialise le sémaphore avec le nombre de tâches dans la file. Sa valeur initiale est zéro. */
  sem_init(&job_queue_count, 0, 0);
}
/* Traite les tâches en attente jusqu’à ce que la file soit vide. */
void *thread_function(void *arg)
{
  while (1)
  {
    struct job *next_job;
    /* Se met en attente sur le sémaphore de la file de tâches. Si sa valeur est positive, indiquant que la file n’est pas vide, décrémente le total d’une unité. Si la file est vide, bloque jusqu’à ce qu’une nouvelle tâche soit mise en attente. */
    sem_wait(&job_queue_count);
    /* Verrouille le mutex sur la file de tâches. */
    pthread_mutex_lock(&job_queue_mutex);
    /* À cause du sémaphore, nous savons que la file n’est pas vide. Récupère donc la prochaine tâche disponible. */
    next_job = job_queue;
    /* Supprime la tâche de la liste. */
    job_queue = job_queue->next;
    /* Déverrouille le mutex de la file d’attente car nous en avons fini avec celle-ci pour le moment. */
    pthread_mutex_unlock(&job_queue_mutex);
    /* Traite la tâche. */
    process_job(next_job);
    /* Libération des ressources. */
    free(next_job);
  }
  return NULL;
}
/* Ajoute une nouvelle tâche en tête de la file. */
void enqueue_job(/* Passez les données sur la tâche ici */)
{
  struct job *new_job;
  /* Alloue un nouvel objet job. */
  new_job = (struct job *)malloc(sizeof(struct job));
  /* Positionner les autres champs de la struct job ici... */
  /* Verrouille le mutex de la file de tâches avant d’y accéder. */
  pthread_mutex_lock(&job_queue_mutex);
  /* Ajoute la nouvelle tâche en tête de file. */
  new_job->next = job_queue;
  job_queue = new_job;
  /* Envoie un signal de réveil sémaphore pour indiquer qu’une nouvelle tâche est disponible. Si des threads sont bloqués en attente sur le sémaphore, l’un d’eux sera débloqué et pourra donc traiter la tâche. */
  sem_post(&job_queue_count);
  /* Déverrouille le mutex de la file de tâches. */
  pthread_mutex_unlock(&job_queue_mutex);
}