// 10 -> 17
//g++ -Wall -std=c++11 -g -o out *.cpp 
#include "Graft.h"
using namespace igwijo;

int main() {
    Graft graft1;
    graft1.set(123456789, "Nelson", "Madiba");
    graft1.print();

    Graft graft2;
    graft2.set(212121212, "Mthuli", "Ncube");
    graft2.print();

    graft1.workerID = 919191919;
    graft1.print();

    return 0;
}