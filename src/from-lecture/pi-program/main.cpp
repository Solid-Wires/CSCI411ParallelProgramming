#include "../../../inc/Common.h"
#define MAX_THREADS 4
using namespace std;

static long num_steps = 1000000000;
static double step;
int main() {
    int i, j;
    double pi, full_sum = 0.0;
    double start_time, run_time;
    double sum[MAX_THREADS];

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
            sum[id] = 0.0;

            if (id == 0) 
            cout << " num_threads = " << numthreads << endl;

            for (i=id; i< num_steps;  i+=numthreads){
                x = (i+0.5)*step;
                sum[id] = sum[id] + 4.0/(1.0+x*x);
            }
        }     //End parallel region

        for(full_sum = 0.0, i=0;i<j;i++)
        full_sum += sum[i];

        pi = step * full_sum;
        run_time = omp_get_wtime() - start_time;
        cout << " pi is "<< pi  <<" in "<< run_time << " seconds,  with " <<j<< " threads " << endl;
    }
}