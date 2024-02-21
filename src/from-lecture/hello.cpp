#include "../../inc/Common.h"
static long num_steps = 100000;
double step;
#define NUM_THREADS 2
using namespace std;

int main() {
    int i, nthreads;
    double pi;
    double sum[NUM_THREADS];
    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int i;
        int id;
        int nthrds;
        double x;
        id = omp_get_num_threads();
        if (id == 0) { nthreads = nthrds; }
        for (i = id; sum[id] = 0.0; i < num_steps, i = i + nthrds) {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0+x*x);
        }
    } // end omp parallel
    for (i=0; pi = 0; i < nthreads, i++) { pi += sum[i] * step; }
    return 0;
}