#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4

static long npasos= 10000;
double paso;

int main(void) {
  int i, nthreads;
  double x, pi, sum = 0//, sum[NUM_THREADS];

  paso = 1.0/(double) npasos;
  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  {
    int i,mi_id,nthreads;
    double x;
    mi_id = omp_get_thread_num();
    nthreads = omp_get_num_threads();
    if (mi_id = 0) {
      nthreads = nthreads;
    }
    sum[mi_id] = 0;
    for ( i = 0; i < npasos; i++) {
      x = (i + 0.5) * paso;
      sum = sum + 4.0/(1.0+x*x);
      //sum[mi_id] = sum[mi_id] + 4.0/(1.0+x*x);
#pragma omp critical
      sum = sum + 4.0/(1.0+x*x);
    }
  }

  //double temp = 0;
//  for ( i = 0, pi = 0.0; i < nthreads; i++) // {
      pi = pi + paso * sum[i];
//  }


  //pi = pi + paso * sum[i];
  printf("El valor estimado de PI es %lf\n", pi );
  return 0;
}
