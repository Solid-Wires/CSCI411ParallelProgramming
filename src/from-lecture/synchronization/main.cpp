#include "../../../inc/Common.h"
#define MAX_THREADS 4
using namespace std;

static long num_steps = 100000000;
int main() {
    int i,j;
    double pi, full_sum = 0.0;
    double start_time, run_time;
    double step = 1.0/(double) num_steps;

    for (j=1;j<=MAX_THREADS ;j++)   // loop for thread count of 1, 2,3,4
    {  
        omp_set_num_threads(j);
        start_time = omp_get_wtime();
        pi = 0.0 ; // reset pi

        #pragma omp parallel
        {
            int i;
            double x,sum;
            int id = omp_get_thread_num();
            int numthreads = omp_get_num_threads();

            for (i=id,sum  = 0.0;i< num_steps; i+=numthreads)
            {
                x = (i+0.5)*step;
                sum = sum + 4.0/(1.0+x*x);
            }

            #pragma omp critical
            {
                pi += sum *step;
            }
        }   // end of parallel region
        run_time = omp_get_wtime() - start_time;
        cout << "\n pi is " << pi  << " in " << run_time  << " seconds,  with " << j << " threads\n" ;  
    }   // end thread loop	
}