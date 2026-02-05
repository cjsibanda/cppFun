//  12
// try g++ -Wall -std=c++11 -g -o out *.cpp
#include "GraftA.h"
using namespace igwijo;

int main() {
    Graft busyBee1;
    busyBee1.set(123456789, "Jacob", "Zuma");
    busyBee1.print();

    Graft busyBee2;
    busyBee2.set(121212121, "Sasha", "Ngomezulu");
    busyBee2.print();

    printTheWorker(busyBee1);
    setTheWorker(busyBee2, 123456789, "Sista", "Betina");
    printTheWorker(busyBee2);
    return 0;
}
