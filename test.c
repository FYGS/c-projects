#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Exemple de fonction traduisant la d´efinition de la suite: 
 * u_0 = 1 
 * u_n = 2*u_{n-1} + 1 si n >= 1
 * 
 * Contrainte: n>=0
 * 
 * @param int indique le rang de la suite
 * @return int les termes de la suite jusqu'au rang indiqué
 */
int ma_suite(unsigned int);

/**
 * @brief imprime les n termes de la suite
 * 
 * @param int spécifie le nombre de termes à afficher
 */
void imprime_suite(unsigned int);

int main(void) {
  int x = 16, y = 3;

  (void)printf("%i << %i = %i\n"
               "%i >> %i = %i\n", x, y, x<<y, x, y, x>>y);

  /**
                * @brief Test ma_suite
                * 
                */
    unsigned int n = 2;
    imprime_suite(n);

  return 0;

}

int ma_suite(unsigned int n) {
  if(n == 0) return 1;
  return (2 * ma_suite(n - 1) + 1);
}

void imprime_suite(unsigned int count) {
  printf("Les %i premiers termes de la suite sont:\n", count + 1);
  for (size_t i = 0; i <= count; i++)
  {
    printf("U%li = %i\n", i, ma_suite(i));
  }
  
}