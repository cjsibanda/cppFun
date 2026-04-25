//Something like this...
//g++ -Wall -std=c++17 -g -o ws file1.cpp file2.cpp
#include <iostream>
#define SIBANDA_FOODORDER_H
#ifndef SIBANDA_FOODORDER_H //header guard

// extern double g_taxrate;
// extern g_dailydiscount; 

namespace sibanda {

class FoodOrder {
    string m_name[10];
    string m_length;  //c_ctyle null-terminated string of any length?
    double m_price;
    bool isSpecial;       
  public:
    FoodOrder(); //Default constructor
    void read(std::istream&);
    void display(std::ostream&, FoodOrder&) const //const?
}

}
#endif