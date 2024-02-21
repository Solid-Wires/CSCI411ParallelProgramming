#include "../../../inc/Common.h"
using namespace std;

int main() {
    long num_steps = 1000000000;
    double step, x, pi, sum = 0.0;
    double start_time, run_time;
    step = 1.0/(double)num_steps;

    for (int i = 1; i <= num_steps; i++) {
        x = (i-0.5)*step;
        sum = sum + 4.0/(1.0+(x*x));
    }
    pi = step * sum;

    cout << " pi with " << num_steps << " steps is " << pi << endl;

    return 0;
}