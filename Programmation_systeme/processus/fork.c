#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  pid_t child_pid;
  printf("ID de processus du programme principal : %d\n", (int)getpid());
  child_pid = fork();
  if (child_pid != 0)
  {
    printf("je suis le processus parent, ID : %d\n", (int)getpid());
    printf("Identifiant du processus fils : %d\n", (int)child_pid);
  }
  else {
    printf("je suis le processus fils, ID : %d\n", (int)getpid());
  }
    
  return 0;
}
