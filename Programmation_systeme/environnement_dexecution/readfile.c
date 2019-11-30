#include <fcntl.h> // O_RDONLY
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char *read_from_file(const char *filename, size_t length)
{
  char *buffer;
  int fd;
  ssize_t bytes_read;
  /* Alloue le tampon. */
  buffer = (char *)malloc(length);
  if (buffer == NULL)
    return NULL;
  /* Ouvre le fichier. */
  fd = open(filename, O_RDONLY);
  if (fd == -1)
  {
    /* L’ouverture a échoué. Libère le tampon avant de quitter. */
    free(buffer);
    return NULL;
  }
  /* Lit les données. */
  bytes_read = read(fd, buffer, length);
  if (bytes_read != length)
  {
    /* La lecture a échoué. Libère le tampon et ferme fd avant de quitter. */
    free(buffer);
    close(fd);
    return NULL;
  }
  /* Tout va bien. Ferme le fichier et renvoie le tampon. */
  close(fd);
  return buffer;
}

// bib. statique ou archive = ens. de fichiers objets:
// ar cr libtest.a fich1.o fich2.o ...

// bib. partagée (dynamique) = ens. de fichiers objets unifié en 1 seul:
// Il faut compiler le prog avec l'option:
//      gcc -c -fPIC test1.c 
// avant de lancer:
//      gcc -shared -fPIC -o libtest.so test1.o test2.o ...  (so == shared object)
//  la lier à un programme se fait comme ceci:
//      gcc -o app app.o -L. -ltest 
// c'est le choix par défaut de l'éditeur de lien, sinon -static

// gcc -o app -L. -ltest app.o -> source d'erreur
// gcc -o app app.o -L. -ltest -> correct