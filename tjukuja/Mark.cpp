
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Mark.h"
using namespace std;

namespace sibanda {

   bool Mark::isValid() const {
      return (m_value >= 0 && m_value <= 100);
   }

   Mark::Mark(int value, char type) {
      *this = type;
      m_value = double(value);
   }

   Mark::Mark(double value) {
      m_type = MARK;
      m_value = value;
   }

   Mark& Mark::operator+=(const Mark& M) {
      m_value += M.m_value;
      return *this;
   }

   Mark& Mark::operator-=(const Mark& M) {
      m_value -= M.m_value;
      return *this;
   }

   Mark Mark::operator+(const Mark& M) const {
      return Mark(*this) += M;
   }

   Mark Mark::operator-(const Mark& M) const {
      return Mark(*this) -= M;
   }

   Mark& Mark::operator/=(int other) {
      m_value = m_value / other;
      return *this;
   }

   Mark Mark::operator/(int other) const {
      return Mark(m_value / other);
   }

   Mark& Mark::operator=(int value) {
      m_value = value;
      return *this;
   }

   Mark& Mark::operator=(char type) {
      m_type = MARK;
      if (type == GRADE || type == GPA) {
         m_type = type;
      }
      return *this;
   }

   double Mark::raw() const {
      return m_value;
   }

   Mark::operator int() const {
      int value = -1;
      if (isValid()) {
         value = int(std::round(m_value < 0 ? 0 : m_value));
      }
      return value;
   }

   Mark::operator bool() const {
      return isValid();
   }

   Mark::operator double() const {
      double gpa = 0;
      if (!isValid()) gpa = -1;
      else gpa = m_value * 0.04;
      return gpa;
   }

   Mark::operator const char* () const {
      char* grade = const_cast<char*>(m_grade);
      int value = int(*this);
      grade[1] = grade[2] = '\0';
      if (value < 0 || value > 100) grade[0] = 'X';
      else if (value >= 90) grade[0] = 'A', grade[1] = '+';
      else if (value >= 80) grade[0] = 'A';
      else if (value >= 75) grade[0] = 'B', grade[1] = '+';
      else if (value >= 70) grade[0] = 'B';
      else if (value >= 65) grade[0] = 'C', grade[1] = '+';
      else if (value >= 60) grade[0] = 'C';
      else if (value >= 55) grade[0] = 'D', grade[1] = '+';
      else if (value >= 50) grade[0] = 'D';
      else grade[0] = 'F';
      return m_grade;
   }

  ///////////////////////////////////////////////////////////////////////
  // this is the display method
  // it should return a reference to an ostream object
  // it receives an ostream reference as a parameter, defaulted to cout
  // if mark is invalid & type is GRADE then print "**" otherwise "***"
  // if type is GPA - print Mark as double, 1 digit afer decimal width of 3
  // if type is MARK - print Mark as int - use width of 3
  // --right-justify the output - fill unsuded width with undescores ('_')
  // if type is GRADE - print Mark as const char* - left justify ouput
  // use a width of 3 - Fill unused width with spaces
  ////////////////////////////////////////////////////////////////////////
   ostream& Mark::display(ostream& os) const {
      if (!isValid()) {
         os << (m_type == GRADE ? "**" : "***");
      } else if (m_type == GPA) {
         os << fixed << setprecision(1) << setw(3) << double(*this);
      } else if (m_type == MARK) {
         os << setfill('_') << setw(3) << right << int(*this);
      } else if (m_type == GRADE) {
         os << setfill(' ') << setw(3) << left << (const char*)(*this);
      }
      return os;
   }

   ////////////////////////////////////////////////////////////////////////
   // this is the display Helper function (non-member)
   // It returns a reference to an ostream object
   // it receives: const reference to mark obj, char for display type
   // it also receives ostream reference (cout)
   // It outputs/prints the Mark object using the MARK display type first
   // if type is NOT Mark .. it appends colon+space followed by same obj
   ////////////////////////////////////////////////////////////////////////
   ostream& display(const Mark& mk, char type, ostream& os) {
      Mark M = mk;
      M = MARK;
      M.display(os);
      if (type != MARK) {
         os << ": ";
         M = type;
         M.display(os);
      }
      return os;
   }


   /////////////////////////////////////////////////////////////////////////////
   // ostream Insertion Helper Operator Overload
   // overload operator<< to allow Mark onbject to be inserted into ostream
   // this operator should behave exactly like the display method of the class
   /////////////////////////////////////////////////////////////////////////////
   ostream& operator<<(ostream& os, const Mark& M) {
      return M.display(os);
   }


   /////////////////////////////////////////////////////////////////////////////
   // istream Extraction Helper Operator Overload
   // overloads the extraction operator (operator>>) to read a Mark object
   // it reads the ark object from an istream in a foolfproof manner
   // function ensures that user enters int between 0 & 100
   // function also ensures that there are no trailing non-digit characters
   /////////////////////////////////////////////////////////////////////////////
   istream& operator>>(istream& is, Mark& M) {
      int val;
      while (true) {
         if (!(is >> val)) {
            cout << "Invalid integer, try again.\n> ";
            is.clear();
            is.ignore(10000, '\n');
            continue;
         }
         char ch = is.peek();
         if (ch != '\n' && ch != EOF) {
            is.ignore(10000, '\n');
            cout << "Invalid trailing characters. Please enter only an integer.\n> ";
            continue;
         }
         if (val < 0 || val > 100) {
            cout << "Invalid mark. Enter a value between 0 and 100.\n> ";
            continue;
         }
         M = val;
         is.ignore(10000, '\n'); // consume newline
         break;
      }
      return is;
   }

   //////////////////////////////////////////////////////////////////////////
   // ifstream Extraction Helper Operator Overload
   // overloads exctraction operator to read a Mark object from an ifstream
   // this operator>> reads the object using the format: mark, type
   // the function: reads int value, ignores the comma
   // the function also: reads a single character representing the type (G,M,R)
   // if state is good after read, Mark object is updated with read values
   // it returns the reference to the input stream
   //////////////////////////////////////////////////////////////////////////
   ifstream& operator>>(ifstream& ifs, Mark& M) {
      int val;
      char comma, type;
      if (ifs >> val >> comma >> type && comma == ',') {
         M = val;
         M = type;
      }
      return ifs;
   }

   /////////////////////////////////////////////////////////////////////////////////////
   // Helper operator+ Overload for double Values
   // Overloads operator+ to support arithmetic between primitive value & Mark
   // Overload operator+ so double is added to raw double value of Mark (returns double)
   /////////////////////////////////////////////////////////////////////////////////////
   double operator+(double lhs, const Mark& rhs) {
      return lhs + rhs.raw();
   }

   /////////////////////////////////////////////////////////////////////////////////////
   // Helper operator+ Overload for int values
   // Overload operator+ to support arithmetic between primitive value & Mark
   // Overload operator+ so int is added to rounded int value of Mark (returns int)
   /////////////////////////////////////////////////////////////////////////////////////
   int operator+(int lhs, const Mark& rhs) {
      return lhs + int(rhs);
   }


   double operator-(double lhs, const Mark& rhs) {
      return lhs - rhs.raw();
   }
   int operator-(int lhs, const Mark& rhs) {
      return lhs - int(rhs);
   }


   double operator/(double lhs, const Mark& rhs) {
      return lhs / rhs.m_value;
   }
   int operator/(int lhs, const Mark& rhs) {
      return lhs / int(rhs);
   }

} // namespace sibanda