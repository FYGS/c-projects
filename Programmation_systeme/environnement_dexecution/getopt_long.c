#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

/* Nom du programme */
const char *program_name;

/* Envoie les informations sur l'utilisation de la commande vers STREAM
(typiquement stdout ou stderr) et quitte le programme avec EXIT_CODE. 
 Ne retourne jamais. */
void print_usage(FILE *stream, int exit_code)
{
  fprintf(stream, "Utilisation : %s options [fichierentrée ...]\n", program_name);
  fprintf(stream, " -h --help Affiche ce message.\n"
                  " -o --output filename Redirige la sortie vers un fichier.\n"
                  " -v --verbose Affiche des messages détaillés.\n");
  exit(exit_code);
}

/* Point d'entrée du programme. ARGC contient le nombre d'éléments de la liste d'arguments ; ARGV est un tableau de pointeurs vers ceux-ci. */
int main(int argc, char *argv[])
{
  int next_option;
  /* Chaîne listant les lettres valides pour les options courtes. */
  const char *const short_options = "ho:v";

  /* Tableau décrivant les options longues valides. */
  const struct option long_options[] = {
      {"help", 0, NULL, 'h'},
      {"output", 1, NULL, 'o'},
      {"verbose", 0, NULL, 'v'},
      {NULL, 0, NULL, 0} /* Requis à la fin du tableau. */
  };

  /* Nom du fichier vers lequel rediriger les sorties, ou NULL pour la sortie standard. */
  const char *output_filename = NULL;
  /* Indique si l'on doit afficher les messages détaillés. */
  int verbose = 0;
  /* Mémorise le nom du programme, afin de l'intégrer aux messages. Le nom est contenu dans argv[0]. */
  program_name = argv[0];
  do
  {
    next_option = getopt_long(argc, argv, short_options, long_options, NULL);

    switch (next_option)
    {
    case 'h': /* -h or --help */
      /* L'utilisateur a demandé l'aide-mémoire. L'affiche sur la sortie standard et quitte avec le code de sortie 0 (fin normale). */
      print_usage(stdout, 0);
    case 'o': /* -o ou --output */
      /* Cette option prend un argument, le nom du fichier de sortie. */
      output_filename = optarg;
      break;
    case 'v': /* -v ou --verbose */
      verbose = 1;
      break;
    case '?': /* L'utilisateur a saisi une option invalide. */
      /* Affiche l'aide-mémoire sur le flux d'erreur et sort avec le code de sortie un (indiquant une fin anormale). */
      print_usage(stderr, 1);
    case -1: /* Fin des options. */
      break;
    default: /* Quelque chose d'autre : inattendu. */
      abort();
    }
  } while (next_option != -1);
  /* Fin des options. OPTIND pointe vers le premier argument qui n'est pas une option. À des fins de démonstration, nous les affichons si l'option verbose est spécifiée. */
  if (verbose)
  {
    int i;
    for (i = optind; i < argc; ++i)
      printf("Argument : %s\n", argv[i]);
  }
  /* Le programme principal se place ici. */
while (1)
{
  //printf("."); // stdout buferisé
  fprintf(stderr, "."); // stderr non bufferisé
  sleep(1);
}


  return 0;
}