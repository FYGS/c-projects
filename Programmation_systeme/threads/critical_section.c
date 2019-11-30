#include <pthread.h>
#include <stdio.h>
#include <string.h>

/* Tableau des soldes de comptes, indexé par numéro de compte. */
float *account_balances;
/* Transfère DOLLARS depuis le compte FROM_ACCT vers TO_ACCT. Renvoie 0 si la transaction s’est bien déroulée ou 1 si le solde de FROM_ACCT est trop faible. */
int process_transaction(int from_acct, int to_acct, float dollars)
{
  int old_cancel_state;
  /* Vérifie le solde de FROM_ACCT. */
  if (account_balances[from_acct] < dollars)
    return 1;
    
  /* Début de la section critique. */
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
  /* Transfère l’argent. */
  account_balances[to_acct] += dollars;
  account_balances[from_acct] -= dollars;
  /* Fin de la section critique. */
  pthread_setcancelstate(old_cancel_state, NULL);
  return 0;
}