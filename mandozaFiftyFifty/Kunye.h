// try g++ -Wall -std=c++11 -g -o out *.cpp

#ifndef MANDOZA_ACCOUNT_H_
#define MANDOZA_ACCOUNT_H_
#include <iostream>

namespace mandoza {
   const int NameMaxLen = 30;
   class Kunye {
      double m_balance;
      int m_number;
      char m_holderName[NameMaxLen + 1];
      void cpyName(const char* src);
      bool isValidNumber(int number)const;
   public:
      Kunye(const char* holderName = nullptr);
      Kunye(const char* holderName, int number, double balance);
      std::ostream& display()const;



      // Conversions
      operator bool() const;
      operator int() const;
      operator double() const;

      // New-state test
      bool operator~() const;

      // Subscript (access holder name)
      char& operator[](int index);
      const char& operator[](int index) const;

      // Assignment
      Kunye& operator=(int number);
      Kunye& operator=(double balance);

      // Arithmetic on balance
      Kunye& operator+=(double value);
      Kunye& operator-=(double value);

      // Transfers
      Kunye& operator<<(Kunye& right);
      Kunye& operator>>(Kunye& right);

      // Unary ++/--
      Kunye& operator++();
      Kunye operator++(int);
      Kunye& operator--();
      Kunye operator--(int);
   };
}
#endif // MANDOZA_ACCOUNT_H_
