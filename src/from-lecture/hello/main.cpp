#include "../../../inc/Common.h"
using namespace std;

int main() {

    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        cout << "Hello(" << id << ")";
        cout << "World(" << id << ")" << endl;
    }

    return 0;
}