#include <stdio.h>

static long npasos= 10000;
double paso;
int main(void) {
  int i;
  double x, pi, sum = 0.0;
  paso = 1.0/(double) npasos;
//#pragma omp parallel for reduction (+:sum)
  for ( i = 0; i < npasos; i++) {
    x = (i + 0.5) * paso;
    sum = sum + 4.0/(1.0+x*x);
  }
  pi = paso * sum;
  printf("El valor estimado de PI es %lf\n", pi );
  return 0;
}
