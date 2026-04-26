//try --> g++ -Wall -std=c++17 -g -o ws file1.cpp file2.cpp
#define SIBANDA_FOODORDER_H
#ifndef SIBANDA_FOODORDER_H //header guard

#include <iostream>

extern double g_taxrate;
extern g_dailydiscount; 

namespace sibanda {

class FoodOrder {
    char m_name[10];
    char* m_length{};  
    double m_price{};
    bool isSpecial{};       
  public:
    FoodOrder(); //Default constructor
    FoodOrder(const FoodOrder& src);
    FoodOrder& operator=(const FoodOrder& src);
    ~FoodOrder();
    void read(std::istream &is);
    void display() const 
  };

}
#endif