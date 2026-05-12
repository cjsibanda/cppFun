#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {
    class FoodOrder{
        char m_name[10]{};
        char* m_description{};
        double m_price{};
        bool isSpecial{};
    public:
        FoodOrder(); //default constructor
        void read(std::istream& is);
        void display() const;
        //rule of 3
        FoodOrder(const FoodOrder& src);
        FoodOrder& operator=(const FoodOrder& src);
        ~FoodOrder();        
    };
}
#endif

// try g++ -Wall -std=c++17 -g -o out *.cpp
// with the txt files, don't use .out