/*
  Este programa calcula el valor de pi usando el método de Monte Carlo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void){
  unsigned long int i;
  unsigned long int Ncirc = 0, intentos;
  double x,y,pi;

  printf("Calculo de pi usando el metodo de Monte Carlo\n");
 
  srand48(time(NULL));

  intentos = 1000000000;
#pragma omp parallel for private(x,y) reduction(+:Ncirc)
  for(i=1;i<=intentos;i++){
    x=drand48();
    y=drand48();
    if((x*x+y*y) <= 1.0){
      //Ncirc++;
      Ncirc = Ncirc + 1;
    }
  }

  printf("Numero de puntos que cayeron adentro: %lu\n",Ncirc);

  pi = 4.0 * ((double)Ncirc / (double) intentos);
  printf("Valor de pi estimado con Montecarlo: %1.10f\n",pi);
  return EXIT_SUCCESS;
}
