#include <pthread.h>

class ThreadExitException
{
public:
  /* Crée une exception signalant la fin d’un thread avec RETURN_VALUE. */
  ThreadExitException(void *return_value)
      : thread_return_value_(return_value)
  {
  } /* Quitte le thread en utilisant la valeur de retour fournie dans le 10 constructeur. */
  void *DoThreadExit()
  {
    pthread_exit(thread_return_value_);
  }

private:
  /* Valeur de retour utilisée lors de la sortie du thread. */
  void *thread_return_value_;
};


void do_some_work()
{
  while (1)
  {
    /* Placer le code utile ici... */
    if (/*should_exit_thread_immediately()*/1)
      throw ThreadExitException(/* thread?s return value = */ NULL);
  }
}
void *thread_function(void *)
{
  try
  {
    do_some_work();
  }
  catch (ThreadExitException ex)
  {
    /* Une fonction a signalé que l’on devait quitter le thread. */
    ex.DoThreadExit();
  }
  return NULL;
}
