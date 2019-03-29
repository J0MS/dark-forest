#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
#define NUM_THREADS 4

//cc -fopenmp  pi_omp.3.c -o pi_omp

static long npasos = 100000;
double paso;

int main(void){
   int i; 
   double x, pi, sum = 0.0;

   paso = 1.0 / (double) npasos;
   omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for private(x) reduction(+:sum)
/*{
   int i, mi_id, nthrds;
   double x,sum;

   mi_id = omp_get_thread_num();
   nthrds = omp_get_num_threads();
   for(i = mi_id, sum=0.0; i<npasos; i=i+nthrds){*/
   for(i=0; i<npasos; i++){
      x = (i + 0.5) * paso;
      sum = sum + 4.0/(1.0+x*x);
   }
//#pragma omp critical
   pi = paso * sum;
//}

   printf("El valor estimado de PI es %lf\n", pi);

   return EXIT_SUCCESS;
}

