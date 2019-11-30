#include <stdlib.h>
#include <unistd.h>

/* Handle sur un fichier temporaire créé avec write_temp_file. Avec cette implémentation, il s’agit d’un descripteur de fichier. */
typedef int temp_file_handle;
/* Écrit LENGTH octets de BUFFER dans un fichier temporaire. Unlink est appelé immédiatement sur le fichier temporaire. Renvoie un handle sur le fichier temporaire. */
temp_file_handle write_temp_file(char *buffer, size_t length)
{
  /* Crée le nom du fichier et le fichier. XXXXXX sera remplacé par des caractères donnant un nom de fichier unique. */
  char temp_filename[] = "/tmp/temp_file.XXXXXX";
  int fd = mkstemp(temp_filename);
  /* Appelle unlink immédiatement afin que le fichier soit supprimé dès que le descripteur sera fermé. */
  unlink(temp_filename);
  /* Écrit le nombre d’octets dans le fichier avant tout. */
  write(fd, &length, sizeof(length));
  /* Écrit des données proprement dites. */
  write(fd, buffer, length);
  /* Utilise le descripteur de fichier comme handle sur le fichier temporaire. */
  return fd;
}
/* Lit le contenu du fichier temporaire TEMP_FILE créé avec write_temp_file. La valeur de retour est un tampon nouvellement alloué avec ce contenu, que l’appelant doit libérer avec free. *LENGTH est renseigné avec la taille du contenu, en octets. Le fichier temporaire est supprimé. */
char *read_temp_file(temp_file_handle temp_file, size_t *length)
{
  char *buffer;
  /* Le handle sur TEMP_FILE est le descripteur du fichier temporaire. */
  int fd = temp_file;
  /* Se place au début du fichier. */
  lseek(fd, 0, SEEK_SET);
  /* Lit les données depuis le fichier temporaire. */
  read(fd, length, sizeof(*length));
  /* Alloue un buffer et lit les données. */
  buffer = (char *)malloc(*length);
  read(fd, buffer, *length);
  /* Ferme le descripteur de fichier ce qui provoque la suppression du fichier temporaire. */
  close(fd);
  return buffer;
}
