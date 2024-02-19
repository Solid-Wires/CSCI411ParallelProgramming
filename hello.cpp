#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    #pragma omp parallel
    {
        cout << " Hello";
        cout << " World" << endl;
    }
    return 0;
}