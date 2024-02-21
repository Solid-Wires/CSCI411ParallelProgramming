#include "../../../inc/Common.h"
using namespace std;

int main() {

    #pragma omp parallel
    {
        int id = omp_get_num_threads();
        cout << "Hello(" << id << ")";
        cout << "World(" << id << ")" << endl;
    }

    return 0;
}