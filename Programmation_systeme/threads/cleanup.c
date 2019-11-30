#include <malloc.h>
#include <pthread.h>

/* Alloue un tampon temporaire. */
void *allocate_buffer(size_t size)
{
  return malloc(size);
}
/* Libère un tampon temporaire. */
void deallocate_buffer(void *buffer)
{
  free(buffer);
}
void do_some_work()
{
  /* Alloue un tampon temporaire. */
  void *temp_buffer = allocate_buffer(1024);
  /* Enregistre un gestionnaire de libération de ressources pour ce tampon pour le libérer si le thread se termine ou est annulé. */
  pthread_cleanup_push(deallocate_buffer, temp_buffer);
  /* Placer ici des traitements qui pourraient appeler pthread_exit ou être annulés... */
  /* Supprime le gestionnaire de libération de ressources. Comme nous passons une valeur différente de zéro, la libération est effectuée par l’appel de deallocate_buffer. */
  pthread_cleanup_pop(1);
}