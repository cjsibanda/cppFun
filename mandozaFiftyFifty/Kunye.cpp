#include <iostream>
#include <cstring>   // for std::strlen
#include "Kunye.h"

using namespace std;

namespace mandoza {

   void Kunye::cpyName(const char* src) {
      int i;
      for (i = 0; src && src[i] && i < NameMaxLen; i++) {
         m_holderName[i] = src[i];
      }
      m_holderName[i] = char(0); 
   }

   bool Kunye::isValidNumber(int number) const {
      return number >= 10000 && number <= 99999;
   }

   Kunye::Kunye(const char* holderName) {
      m_holderName[0] = char(0);
      m_number = -1;
      m_balance = 0.0;
      if (holderName && holderName[0]) {
         cpyName(holderName);
         m_number = 0; 
      }
   }

   Kunye::Kunye(const char* holderName, int number, double balance) {
      m_holderName[0] = char(0);
      m_number = -1;
      m_balance = 0.0;
      if (holderName && holderName[0] && isValidNumber(number)
         && balance > 0) {     
         cpyName(holderName);
         m_number = number;
         m_balance = balance;
      }
   }

   std::ostream& Kunye::display() const {
      if (*this) {
         cout << " ";
         cout.fill(' ');
         cout.width(NameMaxLen);
         cout.setf(ios::left);
         cout << m_holderName;
         cout.unsetf(ios::left);
         cout << " | ";
         cout << m_number;
         cout << " | ";
         cout.width(12);
         cout.precision(2);
         cout.setf(ios::right);
         cout.setf(ios::fixed);
         cout << m_balance;
         cout.unsetf(ios::right);
         cout << " ";
      }
      else if (~*this) {
         cout << " ";
         cout.fill(' ');
         cout.width(30);
         cout.setf(ios::left);
         cout << m_holderName;
         cout.unsetf(ios::left);
         cout << " |  NEW  |         0.00 ";
      }
      else {
         cout << " Bad Account                    | ----- | ------------ ";
      }
      return cout;
   }



   // Valid account: 5-digit number, non-negative balance, non-empty name
   Kunye::operator bool() const {
      return isValidNumber(m_number) && m_balance >= 0.0 && m_holderName[0] != '\0';
   }


   bool Kunye::operator~() const {
      return m_number == 0 && m_holderName[0] != '\0';
   }

   // Conversions
   Kunye::operator int() const    { return m_number; }
   Kunye::operator double() const { return m_balance; }

   // Subscript operators (access holder name safely)
   char& Kunye::operator[](int index) {
      static char placeholder = '\0'; // safe writable fallback for out-of-range
      int len = int(std::strlen(m_holderName));
      if (index >= 0 && index < len) {
         return m_holderName[index];
      }
      return placeholder;
   }

   const char& Kunye::operator[](int index) const {
      static const char nullChar = '\0';
      int len = int(std::strlen(m_holderName));
      if (index >= 0 && index < len) {
         return m_holderName[index];
      }
      return nullChar;
   }

   // Assign a number: only if NEW; invalid input -> invalid empty state
   Kunye& Kunye::operator=(int number) {
      if (~(*this)) {
         if (isValidNumber(number)) {
            m_number = number;
         } else {
            // invalid empty state
            m_number = -1;
            m_balance = 0.0;
            m_holderName[0] = '\0';
         }
      }
      // If already VALID or INVALID, ignore attempts to change number
      return *this;
   }

   // Assign balance: only if VALID and non-negative
   Kunye& Kunye::operator=(double balance) {
      if (*this && balance >= 0.0) {
         m_balance = balance;
      }
      return *this;
   }


   Kunye& Kunye::operator+=(double value) {
      if (*this && value > 0.0) {
         m_balance += value;
      }
      return *this;
   }


   Kunye& Kunye::operator-=(double value) {
      if (*this && value > 0.0 && m_balance >= value) {
         m_balance -= value;
      }
      return *this;
   }

   // Transfer all funds: right -> this
   Kunye& Kunye::operator<<(Kunye& right) {
      if (this != &right && *this && right) {
         m_balance += right.m_balance;
         right.m_balance = 0.0;
      }
      return *this;
   }

   // Transfer all funds: this -> right
   Kunye& Kunye::operator>>(Kunye& right) {
      if (this != &right && *this && right) {
         right.m_balance += m_balance;
         m_balance = 0.0;
      }
      return *this;
   }

   // ++ prefix: add $1 if VALID
   Kunye& Kunye::operator++() {
      if (*this) m_balance += 1.0;
      return *this;
   }

   // ++ postfix: return old, then add $1 if VALID
   Kunye Kunye::operator++(int) {
      Kunye old = *this;
      if (*this) m_balance += 1.0;
      return old;
   }

   // -- prefix: subtract $1 if VALID and enough balance
   Kunye& Kunye::operator--() {
      if (*this && m_balance >= 1.0) m_balance -= 1.0;
      return *this;
   }

   // -- postfix: return old, then subtract $1 if VALID and enough balance
   Kunye Kunye::operator--(int) {
      Kunye old = *this;
      if (*this && m_balance >= 1.0) m_balance -= 1.0;
      return old;
   }
}


