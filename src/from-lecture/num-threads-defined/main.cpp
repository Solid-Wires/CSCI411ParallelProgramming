#include "../../../inc/Common.h"
using namespace std;

void Foo(int, double[1000]);

int main() {
    double A[1000];
    
    cout << "max threads: " << omp_get_max_threads() << endl;
    omp_set_num_threads(4);
    cout << "max threads: " << omp_get_max_threads() << endl;
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        Foo(id, A);
    }
    cout << "All done" << endl;
}

void Foo(int myId, double myA[1000]) {
    cout << "thread: " << myId << endl;
    return;
}
