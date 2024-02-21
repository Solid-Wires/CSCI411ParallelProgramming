#include "../../../inc/Common.h"
using namespace std;

int main() {

    #pragma omp parallel
    {
        cout << "Hello";
        cout << "World" << endl;
    }

    return 0;
}