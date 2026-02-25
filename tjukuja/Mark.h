#ifndef SENECA_MARK_H
#define SENECA_MARK_H
#include <iostream>
#include <fstream>

//9
const char GPA = 'G';
const char MARK = 'M';
const char GRADE = 'R';

namespace sibanda {
   class Mark {
      char m_grade[3]{};
      double m_value;
      char m_type;
      bool isValid() const;
   public:
      Mark(int value = 0, char type = 'M');
      Mark(double value);
      Mark& operator+=(const Mark& other);
      Mark& operator-=(const Mark& other);
      Mark operator+(const Mark& other) const;
      Mark operator-(const Mark& other) const;
      Mark& operator/=(int other);
      Mark operator/(int other) const;
      Mark& operator=(int value);
      Mark& operator=(char type);
      double raw() const;
      operator int() const;
      operator double() const;
      operator const char* () const;
      operator bool() const;

      std::ostream& display(std::ostream& os = std::cout) const;


      friend double operator/(double lhs, const Mark& rhs);
      friend int operator/(int lhs, const Mark& rhs);
   };


   // Non-member helpers
   std::ostream& display(const Mark& M, char type, std::ostream& os = std::cout);
   std::ostream& operator<<(std::ostream& os, const Mark& M);
   std::istream& operator>>(std::istream& is, Mark& M);
   std::ifstream& operator>>(std::ifstream& is, Mark& M);
   double operator+(double lhs, const Mark& rhs);
   int operator+(int lhs, const Mark& rhs);
   double operator-(double lhs, const Mark& rhs);
   int operator-(int lhs, const Mark& rhs);
}
#endif // !SENECA_MARK_H
