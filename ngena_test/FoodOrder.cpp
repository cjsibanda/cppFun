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

    FoodOrder::FoodOrder() {
        //initializing members to safe empty states
        m_name[0] = '\0';
        m_description = nullptr;
        m_price = 0.0;
        isSpecial = false;
    }

    /****************************************************
    - read modifier receives an istream reference
    - if istream is in a good state, the function will attempt
    to read from the istream and store the info read into current object
    - Format:
    <Customer Name>,<Order Description>,<Price>,<Daily Special Status>[newline]
    - the daily special can be of two values: 'Y' and 'N'
    - review Input/Output Objects
    **********************************************************/
    void FoodOrder::read(std::istream& is)
    {
        if (!is) return;

    // Read Name
    is.getline(m_name, 10, ',');

    // Cleanup and Read Description
    delete[] m_description;
    m_description = nullptr;

    string buffer;
    getline(is, buffer, ',');
    m_description = new char[buffer.length() + 1];
    strcpy(m_description, buffer.c_str());

    // Read the Price
    is >> m_price;
    is.ignore(); // skip the comma after price

    // Reads  Special Status
    char special;
    is >> special;
    isSpecial = (special == 'Y');
    
    // clears the trailing newline/extra characters 
    // the next 'ordertag' read in main() starts fresh
    is.ignore(1000, '\n');
    }

    /*******************************
    - dispaly(): a query that displays to the screen 
    the content of a FoodOrder instance
    - Format:
    COUNTER. Name          |Order Description        |Price w/Tax |Special Price
    - if no Customer name has been stored, print:
     COUNTER. No Order
    - COUNTER is a left aligned field of size 2
    - COUNTER holds the number of times this function has been used
    - NOTE don't use global/member variables to store counter
    - Name: is left aligned filed of size 10
    - Order Description: is left aligned field of size 25
    - Pricew/Tax: is a left aligned field of size 12
    - Special Price: is right aligned field of size 13  
    *******************************/ 
    void FoodOrder::display() const
    {
        static size_t numOrders = 0;
        cout << left << setw(2) << ++numOrders << ". ";

        if (m_name[0])
        {
            double priceTaxed = m_price + (m_price * g_taxrate);

            cout << setw(10) << m_name << "|"
                 << setw(25) << m_description << "|"
                 << fixed << setw(12) << setprecision(2)
                 << priceTaxed << "|";

            if (isSpecial)
                cout << right << setprecision(2)
                     << setw(13)
                     << priceTaxed - g_dailydiscount;
        }
        else
        {
            cout << "No Order";
        }

        cout << endl;
    }

    FoodOrder::~FoodOrder()
    {
        delete[] m_description;
    }

    FoodOrder::FoodOrder(const FoodOrder& src)
    {
        *this = src;
    }

    FoodOrder& FoodOrder::operator=(const FoodOrder& src)
    {
        if (this != &src)
        {
            delete[] m_description;
            m_description = nullptr;

            //Shallow copy
            strcpy(m_name, src.m_name);
            m_price = src.m_price;
            isSpecial = src.isSpecial;

            //Deep Copy
            if (src.m_description)
            {
                m_description = new char[strlen(src.m_description) + 1];
                strcpy(m_description, src.m_description);
            }
        }

        return *this;
    }

}

// try g++ -Wall -std=c++17 -g -o out *.cpp
//use ./out day1.txt day2.txt