// try g++ -Wall -std=c++11 -g -o out *.cpp
// for eductational and testing purposes only

#include <iostream>
using namespace std;

#include "RugbyPlayer.h"
using namespace springboks;

int main() {
    RugbyPlayer base;
    MinutesLimitedlayer derived;

    base.read(cin);
    
    cout << endl;

    derived.read(cin);

    derived.print(cout);

    cout << endl;

    derived.setHeartRate(40).setMinutesPlayed(40);
    derived.print(cout);
    // don't do this ^^^ for base

    return 0;

}
