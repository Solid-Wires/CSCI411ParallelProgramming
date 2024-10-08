#include "../../inc/Common.h"
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
double Trap(double a, double b, int n, double h);

// START of main function
int main() {
   double  integral;   /* Store result in integral   */
   double  a, b;                 /* Left and right endpoints      */
   int     n;                    /* Total number of trapezoids    */
   double  h;                    /* Width of trapezoids       */
   int     thread_count;

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
    // Calculate Width of the trapezoid
    h = (b-a)/n;

    //*************************************************
    // Call integration function
    //*************************************************
    integral = Trap(a, b, n, h);

    cout << "With n = " << n << " trapezoids, our estimate of the integral from points "  
            << a << " to " << b << " is " << integral  << endl;

    return EXIT_SUCCESS;
}  /* main */

/*------------------------------------------------------------------
 * Function:    Trap
 * Purpose:     Estimate integral from a to b of f using trap rule and
 *              n trapezoids
 * Input args:  a, b, n, h
 * Return val:  Estimate of the integral 
 */
double Trap(double a, double b, int n, double h) {
   double integral;
   int k;

   integral = (f(a) + f(b))/2.0;
   for (k = 1; k <= n-1; k++) {
     integral += f(a+k*h);
   }
   integral = integral*h;

   return integral;
}  /* Trap */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
   double return_val;

   return_val = x*x;
   return return_val;
}  /* f */