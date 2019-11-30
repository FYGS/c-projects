#include <stdio.h>  // perror
#include <string.h> // strerror
#include <errno.h>  // errno

int main()
{

  const char *path, *user_id;

  int rval = chown(path, user_id, -1);
  if (rval != 0)
  {                         
    /* Sauvegarde errno car il sera écrasé par le prochain appel système */
    int error_code = errno; 
    /* L’opération a échoué ; chown doit retourner -1 dans ce cas. */
    assert(rval == -1);     
    /* Effectue l’action appropriée en fonction de la valeur de errno. */
    switch (error_code)
    {
    case EPERM:                                                                                             /* Permission refusée. */
    case EROFS:                                                                                             /* PATH est sur un système de fichiers en lecture seule */
    case ENAMETOOLONG:                                                                                      /* PATH est trop long. */
    case ENOENT:                                                                                            /* PATH n’existe pas. */
    case ENOTDIR:                                                                                           /* Une des composantes de PATH n’est pas un répertoire */
    case EACCES: 
      /* Une des composantes de PATH n’est pas accessible. */                                    /* Quelque chose ne va pas. Affiche un message d’erreur. */
      fprintf(stderr, "erreur lors du changement de propriétaire de %s: %s\n", path, strerror(error_code)); /* N’interrompt pas le programme ; possibilité de proposer à l’utilisateur de choisir un autre fichier... */
      break;
    case EFAULT: /* PATH contient une adresse mémoire invalide. Il s’agit sûrement d’un bogue */
      abort();
    case ENOMEM: /* Plus de mémoire disponible. */
      fprintf(stderr, "%s\n", strerror(error_code));
      exit(1);
    default: /* Autre code d’erreur innatendu. Nous avons tenté de gérer tous les codes d’erreur possibles ; si nous en avons oublié un il s’agit d’un bogue */
      abort();
    };
  }

  return 0;
}