#include "../../../inc/Common.h"
#define MAX_THREADS 4
#define PAD 8 // Assume 64 byte L1 cache line size
using namespace std;

// Results show that increasing the amount of threads results in poor scaling.
// This is because each thread shares the same cache line, which causes something
// called "false sharing" and therefore makes hardly any difference to performance.

// Solution: pad array elements by a fixed value to adjust cache lines. You'll need to
// initialize the array by PAD and then always access the first element.
// Now the thread performance scaling makes sense!

static long num_steps = 1000000000;
static double step;
int main() {
    int i, j;
    double pi, full_sum = 0.0;
    double start_time, run_time;
    double sum[MAX_THREADS][PAD];

    step = 1.0/(double)num_steps;

    for (j = 1; j <= MAX_THREADS; j++) { // Run test for 1, 2, 3, 4 thread count
        omp_set_num_threads(j);
        full_sum=0.0;
        start_time = omp_get_wtime();

        #pragma omp parallel
        {
            int i;
            int id = omp_get_thread_num();
            int numthreads = omp_get_num_threads();
            double x;
            sum[id][0] = 0.0;

            // Print only if the first thread ran
            if (id == 0) 
                cout << " num_threads = " << numthreads << endl;

            // Calculation towards pi
            for (i = id; i < num_steps;  i += numthreads){
                x = (i+0.5)*step;
                sum[id][0] = sum[id][0] + 4.0/(1.0+x*x);
            }
        }     //End parallel region

        for(full_sum = 0.0, i = 0; i < j; i++)
            full_sum += sum[i][0];

        pi = step * full_sum;
        run_time = omp_get_wtime() - start_time;
        cout << " pi is "<< pi  <<" in "<< run_time << " seconds,  with " <<j<< " threads " << endl;
    }
}