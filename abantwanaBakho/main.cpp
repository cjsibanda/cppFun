//g++ -Wall -std=c++11 -g -o out *.cpp
#include <iostream>
#include "safari.h"

using namespace std;

Safari createSafari() {
    Safari s;
    s.addPlace("Victoria Falls");
    s.addPlace("Harare");
    return s; //<--move semantics here
}

int main() {
    Safari trip1;

    trip1.addPlace("Cape Town");
    trip1.addPlace("Durban");

    cout << "Trip 1:\n";
    trip1.print();
    
    //copy semantics
    Safari trip2 = trip1;

    cout << "\nTrip 2 (copy):\n";
    trip2.print();

    //move semantics
    Safari trip3 = createSafari();

    cout << "\nTrip 3 (moved from function):\n";
    trip3.print();

    //Move assignment
    Safari trip4;
    trip4 = std::move(trip1);

    cout << "\nTrip 4 (moved fromTrip 1):\n";
    trip4.print();

    cout << "\nTrip 1 after move:\n";
    trip1.print(); 

    return 0;

}