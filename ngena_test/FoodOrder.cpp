//hope this works...
//mix and match

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "FoodOrder.h"

using namespace std;

double g_taxrate = 0;
double g_dailydiscount = 0;

namespace seneca 
{
    void FoodOrder::read(std::istream& is)
    {
        is.getline(m_name, 10, ',');

        if (m_description)
            delete[] m_description;

            string buffer;
            getline(is, buffer, ',');

            m_description = new char[buffer.length() + 1];
            strcpy(m_description, buffer.c_str());

            is >> m_price;
            char tmp{ 'N' };
            is.ignore();
            is >> tmp;
            tmp == 'N' ? isSpecial = false : isSpecial = true;
    }
}

void FoodOrder::display() const
{
    static size_t numOrders = 0;
    cout << left << setw(2) << ++numOrders << ". ";
    if (m_name[0])
    {
        double priceTaxed = m_price + (m_price * g_taxrate);
        cout << setw(10) << m_name << "|"
             << setw(25) << m_description << "|"
             << fixed << setw(12) << setprecision(2) << priceTaxed << "|";
        if (isSpecial)
               cout << right << setprecision(2) << setw(13) << priceTaxed - g_dailydiscount;     
    }
    else
       cout << "No Order";
    cout << endl;
}

FoodOrder::~FoodOrder()
{
    delete [] m_description;
}

FoodOrder::FoodOrder(const FoodOrder& src)
{
    *this = src;
}

FoodOrder& FoodOrder::operator=(const FoodOrder& src)
{
    if (this != &src)
    {
        delete [] m_description;
        m_orderDesc = nullptr;

        //Shallow copy
        strcpy(m_name, scr.m_name);
        m_price = src.m_price;
        m_isSpecial = src.m_isSpecial;

        //Deep Copy
        if (src.m_description)
        {
            m_description = new char [strlen(src.m_description) + 1];
            strcpy(m_description, src.m_description);
        }

    }
    return *this;
}

// try g++ -Wall -std=c++17 -g -o out *.cpp