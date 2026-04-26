#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "FoodOrder.h"
using namespace std;

double g_taxRate = 0;
double g_dailydiscount = 0;

namespace sibanda 
{
  void FoodOrder::read(istream& is)
  {
    if (is)
    {
      is.getline(m_customerName, 10, ',');

      if (m_orderDesc)
        delete[] m_orderDesc;

      string buffer;
      getLine(is, buffer, ',');

      m_orderDesc = new char[buffer.length() + 1];
      strcpy(m_orderDesc, buffer.c_str());

      is >> m_price;
      char tmp{ 'N' };
      is.ignore();
      is >> tmp;
      tmp == 'N' ? m_dailyspecial = false : m_dailyspecial = true;
    }
  }

  void FoodOrder::display() const
  {
    static size_t numOrders = 0;
    cout << left << setw(2) << ++numOrders << ". ";
    if (m_customerName[0])
    {
      double priceTaxed = m_price +(m_price * g_taxRate);
      cout << setw(10) << m_customerName << "|"
           << setw(25) << m_orderDesc << "|"
           << fixed << setw(12) << setprecision(2) << priceTaxed << "|";
      if (m_dailyspecial)
         cout << right << setprecision(2) << setw(13) << priceTaxed - g_dailydiscount;
    }
    else
      cout << "No order";
    cout << endl;
  }

  FoodORder::~FoodOrder()
  {
    delete [] m_orderDesc;
  }

  FoodOrder::FoodOrder(const FoodOrder& src)
  {
    *this = src;
  }

  FoodOrder& FoodOrder::operator=(const FoodOrder& src)
  {
    if (this != &src)
    {
      delete [] m_orderDesc;
      m_orderDesc = nullptr;

      //Shallow copy
      strcpy(m_customerName, src.m_customerName);
      m_price = src.m_price;
      m_dailyspecial = src.m_dailyspecial;

      //Deep copy
      if(src.m_orderDesc)
      {
        m_orderDesc = new char [strlen(src.m_orderDesc) + 1];
        strcpy(m_orderDesc, src.m_orderDesc);
      }
    }
    return *this;
  }
}