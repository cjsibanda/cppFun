#include <iostream>
using namespace std;

#include "Worker.h"
using namespace sibanda;

int main() {

    int* hours = new int[5] {2,4,5,6,7};
    Worker worker1(101020305, "Mthuli", "Ncube", 5, hours);
    worker1.print();

    Worker worker2 = worker1;
    worker2.print();

    return 0;
}