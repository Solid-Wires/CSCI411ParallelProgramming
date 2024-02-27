#include "../inc/Common.h"
#define PAD 8 // Assume 64 byte L1 cache line size
using namespace std;
/* File:    Trap.cpp
 * Purpose: Calculate definite integral using trapezoidal 
 *          rule.
 *
 * Input:   a, b, n
 * Output:  Estimate of integral from a to b of f(x)
 *          using n trapezoids.
 *
 * Compile: gcc -g -Wall -o trap trap.c
 * Usage:   ./trap
 *  (JW modified - make does this for you in this source)
 *
 * Note:    The function f(x) is hardwired.
 *
 * IPP:     Section 3.2.1 (pp. 94 and ff.) and 5.2 (p. 216)
 */

// Function Declarations
double f(double x);    /* Function we're integrating */
double TrapParallel(double a, double b, int n, double h);

// START of main function
int main() {
   double  integral;   /* Store result in integral   */
   double  a, b;                 /* Left and right endpoints      */
   int     n;                    /* Total number of trapezoids    */
   double  h;                    /* Width of trapezoids       */
   int     thread_count;    // How many threads to run in parallel to help with computations
   double start_time, run_time;
   
   //*************************************************
   // Establish paramaters for the integral function
   //************************************************
   // Request input from user : THREAD COUNT
   cout << "Enter Thread Count : " ;
   cin >> thread_count;
    if (cin.fail())
	{cout << "ERROR: ";
		cout << "   Input error on left or right endpoints \n" ;
		return EXIT_FAILURE;
	}
   // Request input from user : ENDPOINTS
   cout << "Enter the left and right enpoints of the integral: ";
   cin >> a >> b;
   if (cin.fail())
	{cout << "ERROR: ";
		cout << "   Input error on left or right endpoints \n" ;
		return EXIT_FAILURE;
	}
    // Request input from user : NUMBER OF TRAPEZOIDAL SECTIONS		
    cout << "Enter the number of trapezoids: " ;
    cin >> n;
    if ((n <=0) or (n%thread_count!= 0) or cin.fail())
    {cout << "ERROR: \n";
        cout << "Number of trapzoids " << n << "   Thread count " <<thread_count 
            << " division " << thread_count%n << " cin " << cin.fail() << endl;
        cout << "   number of trapezoids must be evenly divisible by the thread count\n"
            << "   and a number greater than zero \n";
            return EXIT_FAILURE;
    }

    // Timing start
    start_time = omp_get_wtime();

    // Calculate Width of the trapezoid
    h = (b-a)/n;

    // Parallel optimization
    omp_set_num_threads(thread_count);
    // Are we actually getting that many threads? This will tell you.
    int actualThreads = omp_get_max_threads();
    if (actualThreads < thread_count) {
        cout << "Actually using " << actualThreads << " threads (got capped)" << endl;
    }

    //*************************************************
    // Call integration function
    //*************************************************
    integral = TrapParallel(a, b, n, h);

    // Timing end
    run_time = omp_get_wtime() - start_time;

    // Results
    cout << "With n = " << n << " trapezoids, our estimate of the integral from points "  
            << a << " to " << b << " is " << integral  << endl;
    cout << "It took " << run_time << " seconds with " << thread_count << " threads" << endl;
    
    return EXIT_SUCCESS;
}  /* main */

/*------------------------------------------------------------------
 * Function:    TrapParallel
 * Purpose:     Estimate integral from a to b of f using trap rule and
 *              n trapezoids with parallel threads
 * Input args:  a, b, n, h
 * Return val:  Estimate of the integral 
 */
double TrapParallel(double a, double b, int n, double h) {
    double integral = (f(a) + f(b))/2.0;

    // Each thread is keeping track of a sum
    double sum[omp_get_max_threads()][PAD];

    // Parallel region
    #pragma omp parallel
    {
        // Thread information
        int tid = omp_get_thread_num();
        int numthreads = omp_get_num_threads();

        // Parallel iteration (basically the same as what was there before)
        for (int k = tid + 1; k <= n - 1; k += numthreads) {
            double x = a+k*h;
            sum[tid][0] += f(x);
        }

        // At the end of summations, add sum into the integral and multiply by h.
        // The threads shouldn't do this all at once, otherwise there will be
        // computational problems.
        // #pragma omp critical // Same as a mutex
        // {
        //     integral += sum;
        // }
    } // End of parallel region
    for (int tid = 0; tid < omp_get_max_threads(); tid++) {
        integral += sum[tid][0];
    }

    integral *= h;

    return integral;
}  /* TrapParallel */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
   return x*x;
}  /* f */