#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Numbers.h"

using namespace std;

namespace sibanda {

   bool Numbers::isEmpty() const {
      return m_numbers == nullptr || m_numCount == 0;
   }

   void Numbers::setEmpty() {
      m_numbers = nullptr;
      m_filename = nullptr;
      m_numCount = 0;
      m_isOriginal = false;
   }

   void Numbers::setFilename(const char* filename) {
      delete[] m_filename;
      m_filename = new char[strlen(filename) + 1];
      strcpy(m_filename, filename);
   }

   Numbers::Numbers() {
      setEmpty();
   }

   int Numbers::numberCount() const {
      if (!m_filename) return 0;
      ifstream file(m_filename);
      int count = 0;
      char ch;
      while (file.get(ch)) {
         if (ch == '\n') count++;
      }
      return count;
   }

   bool Numbers::load() {
      if (m_numCount <= 0) return false;

      m_numbers = new double[m_numCount];
      ifstream file(m_filename);

      int i = 0;
      while (i < m_numCount && file >> m_numbers[i])
         i++;

      if (i != m_numCount) {
         delete[] m_numbers;
         m_numbers = nullptr;
         m_numCount = 0;
         return false;
      }
      sort();
      return true;
   }

   void Numbers::save() const {
      if (!m_isOriginal || isEmpty()) return;

      ofstream file(m_filename);
      for (int i = 0; i < m_numCount; i++)
         file << m_numbers[i] << endl;
   }

   Numbers::Numbers(const char* filename) {
      setEmpty();

      if (filename) {
         setFilename(filename);
         m_isOriginal = true;
         m_numCount = numberCount();

         if (!load()) {
            delete[] m_filename;
            setEmpty();
         }
      }
   }

   void Numbers::sort() {
      for (int i = 0; i < m_numCount - 1; i++) {
         for (int j = i + 1; j < m_numCount; j++) {
            if (m_numbers[i] > m_numbers[j]) {
               double t = m_numbers[i];
               m_numbers[i] = m_numbers[j];
               m_numbers[j] = t;
            }
         }
      }
   }

   Numbers::Numbers(const Numbers& other) {
      setEmpty();
      m_isOriginal = false;
      *this = other;
   }

   Numbers& Numbers::operator=(const Numbers& other) {
      if (this != &other) {

         delete[] m_numbers;
         delete[] m_filename;

         m_numbers = nullptr;
         m_filename = nullptr;
         m_numCount = other.m_numCount;
         m_isOriginal = false;

         if (other.m_filename) {
            setFilename(other.m_filename);
         }

         if (other.m_numbers && other.m_numCount > 0) {
            m_numbers = new double[other.m_numCount];
            for (int i = 0; i < other.m_numCount; i++)
               m_numbers[i] = other.m_numbers[i];
         }
      }
      return *this;
   }

   Numbers::~Numbers() {
      save();
      delete[] m_numbers;
      delete[] m_filename;
   }

   double Numbers::max() const {
      double m = m_numbers[0];
      for (int i = 1; i < m_numCount; i++)
         if (m_numbers[i] > m) m = m_numbers[i];
      return m;
   }

   double Numbers::min() const {
      double m = m_numbers[0];
      for (int i = 1; i < m_numCount; i++)
         if (m_numbers[i] < m) m = m_numbers[i];
      return m;
   }

   double Numbers::average() const {
      double sum = 0;
      for (int i = 0; i < m_numCount; i++)
         sum += m_numbers[i];
      return sum / m_numCount;
   }

   Numbers& Numbers::operator+=(double value) {
      if (!isEmpty()) {
         double* temp = new double[m_numCount + 1];

         for (int i = 0; i < m_numCount; i++)
            temp[i] = m_numbers[i];

         temp[m_numCount++] = value;

         delete[] m_numbers;
         m_numbers = temp;

         sort();
      }
      return *this;
   }

   ostream& Numbers::display(ostream& ostr) const {

      if (isEmpty()) {
         ostr << "Empty list";
         return ostr;
      }

      ostr << fixed << setprecision(2);
      ostr << "=========================\n";

      if (m_isOriginal)
         ostr << m_filename << endl;
      else
         ostr << "*** COPY ***\n";

      for (int i = 0; i < m_numCount; i++) {
         ostr << m_numbers[i];
         if (i < m_numCount - 1) ostr << ", ";
      }

      ostr << "\n-------------------------\n";
      ostr << "Total of " << m_numCount << " number(s)\n";
      ostr << "Largest number:  " << max() << endl;
      ostr << "Smallest number: " << min() << endl;
      ostr << "Average:         " << average() << endl;
      ostr << "=========================";

      return ostr;
   }

   ostream& operator<<(ostream& os, const Numbers& N) {
      return N.display(os);
   }

   istream& operator>>(istream& is, Numbers& N) {
      double value;
      if (is >> value)
         N += value;
      return is;
   }
}

