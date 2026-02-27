#ifndef SIBANDA_NUMBERS_H_
#define SIBANDA_NUMBERS_H_
#include <iostream>

namespace sibanda {
   class Numbers {
      double* m_numbers;
      char* m_filename;
      bool m_isOriginal;
      int m_numCount;

      bool isEmpty() const;
      void setEmpty();
      void setFilename(const char* filename);
      void sort();

      //added
      int numberCount() const;
      bool load();
      void save() const;

   public:
      Numbers();
      Numbers(const char* filename);
      Numbers(const Numbers& other);
      Numbers& operator=(const Numbers& other);
      ~Numbers();

      double average() const;
      double max() const;
      double min() const;
      
      //added
      Numbers& operator+=(double value);
      std::ostream& display(std::ostream& ostr = std::cout) const;

      friend std::ostream& operator<<(std::ostream& os, const Numbers& N);
      friend std::istream& operator>>(std::istream& is, Numbers& N);
   };
}
#endif