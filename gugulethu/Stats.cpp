#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include "Stats.h"

using namespace std;
namespace sibanda {

   // Sets the object to a safe empty state
   void Stats::setEmpty() {
      delete[] m_numbers;
      delete[] m_filename;
      m_numbers = nullptr;
      m_filename = nullptr;
      m_numCount = 0;
   }

   // Manages dynamic memory for the filename and handles "C_" prefix for copies
   void Stats::setFilename(const char* name, bool isCopy) {
      delete[] m_filename;
      if (name) {
         m_filename = new char[strlen(name) + (isCopy ? 3 : 1)];
         if (isCopy) strcpy(m_filename, "C_");
         else m_filename[0] = '\0';
         strcat(m_filename, name);
      } else {
         m_filename = nullptr;
      }
   }

   // Loads comma-separated numbers from the file into the dynamic array
   void Stats::load() {
      if (m_filename) {
         ifstream f(m_filename);
         string val;
         unsigned count = 0;
         while (getline(f, val, ',')) count++;
         
         if (count > 0) {
            m_numCount = count;
            m_numbers = new double[m_numCount];
            f.clear();
            f.seekg(0);
            for (unsigned i = 0; i < m_numCount; i++) {
               getline(f, val, ',');
               m_numbers[i] = stod(val);
            }
         }
      }
   }

   // Saves current array data into the file as comma-separated values
   void Stats::save() const {
      if (m_filename && m_numbers) {
         ofstream f(m_filename);
         for (unsigned i = 0; i < m_numCount; i++) {
            f << m_numbers[i] << (i == m_numCount - 1 ? "" : ",");
         }
      }
   }

   Stats::Stats(unsigned width, unsigned cols, unsigned prec) 
      : m_columnWidth(width), m_noOfColumns(cols), m_precision(prec) {}

   Stats::Stats(const char* fname, unsigned width, unsigned cols, unsigned prec) 
      : m_columnWidth(width), m_noOfColumns(cols), m_precision(prec) {
      if (fname) {
         setFilename(fname);
         load();
      }
   }

   // Copy Constructor: Implements Rule of Three with file duplication
   Stats::Stats(const Stats& other) {
      m_columnWidth = other.m_columnWidth;
      m_noOfColumns = other.m_noOfColumns;
      m_precision = other.m_precision;
      if (other.m_filename) {
         setFilename(other.m_filename, true);
         m_numCount = other.m_numCount;
         if (m_numCount > 0) {
            m_numbers = new double[m_numCount];
            for (unsigned i = 0; i < m_numCount; i++) m_numbers[i] = other.m_numbers[i];
            save(); // Create the actual file on disk
         }
      }
   }

   // Copy Assignment: Implements Rule of Three with file overwrite
   Stats& Stats::operator=(const Stats& other) {
      if (this != &other) {
         m_columnWidth = other.m_columnWidth;
         m_noOfColumns = other.m_noOfColumns;
         m_precision = other.m_precision;
         if (other.m_numbers) {
            delete[] m_numbers;
            m_numCount = other.m_numCount;
            m_numbers = new double[m_numCount];
            for (unsigned i = 0; i < m_numCount; i++) m_numbers[i] = other.m_numbers[i];
            save(); // Overwrite target file
         }
      }
      return *this;
   }

   Stats::~Stats() {
      delete[] m_numbers;
      delete[] m_filename;
   }

   // Sorts the internal array using std::sort
   void Stats::sort(bool ascending) {
      if (ascending) std::sort(m_numbers, m_numbers + m_numCount);
      else std::sort(m_numbers, m_numbers + m_numCount, std::greater<double>());
   }

   unsigned Stats::size() const { return m_numCount; }

   const char* Stats::name() const { return m_filename; }

   // Returns reference with "loop-back" logic: if size is 10, index 10 returns index 0
   double& Stats::operator[](unsigned idx) {
      if (!*this) return m_dummy;
      return m_numbers[idx % m_numCount];
   }

   double Stats::operator[](unsigned idx) const {
      if (!*this) return 0.0;
      return m_numbers[idx % m_numCount];
   }

   Stats::operator bool() const { return m_numbers != nullptr && m_numCount > 0; }

   // Displays subset of numbers and returns count
   unsigned Stats::occurrence(double min, double max, ostream& ostr) {
      unsigned count = 0;
      if (*this) {
         // This logic leverages operator<< for formatted output
         // Usually requires creating a temporary Stats object or manual formatting
         ostr << fixed << setprecision(m_precision);
         for (unsigned i = 0; i < m_numCount; i++) {
            if (m_numbers[i] >= min && m_numbers[i] <= max) {
               ostr << setw(m_columnWidth) << m_numbers[i];
               count++;
               if (count % m_noOfColumns == 0) ostr << endl;
            }
         }
         if (count % m_noOfColumns != 0) ostr << endl;
         ostr << "Total of " << count << " numbers found in range [" << min << ", " << max << "]" << endl;
      }
      return count;
   }

   // Insertion operator: Displays numbers in tabular format
   ostream& operator<<(ostream& os, const Stats& S) {
      if (S) {
         os << S.m_filename << endl;
         os << string(strlen(S.m_filename), '=') << endl;
         os << fixed << setprecision(S.m_precision);
         for (unsigned i = 0; i < S.m_numCount; i++) {
            os << setw(S.m_columnWidth) << S.m_numbers[i];
            if ((i + 1) % S.m_noOfColumns == 0 && i != S.m_numCount - 1) os << endl;
         }
         os << endl << "Total of " << S.m_numCount << " numbers." << endl;
      } else {
         os << "Empty object";
      }
      return os;
   }

   // Extraction operator: Reads filename from user and loads data
   istream& operator>>(istream& is, Stats& S) {
      string fname;
      if (is >> fname) {
         S.setEmpty();
         S.setFilename(fname.c_str());
         S.load();
      }
      return is;
   }
}