#ifndef SIBANDA_STATS_H_
#define SIBANDA_STATS_H_
#include <iostream>

//11

namespace sibanda {
   class Stats {
      // Dynamic array to store the numbers
      double* m_numbers{};
      // Dynamic string to store the filename
      char* m_filename{};
      // Array size tracking
      unsigned m_numCount{};
      // Formatting variables
      unsigned m_columnWidth{};
      unsigned m_noOfColumns{};
      unsigned m_precision{};
      // Dummy variable for out-of-bounds reference return
      double m_dummy{};

      // Private Methods
      void setEmpty();
      void setFilename(const char* name, bool isCopy = false);
      void load();
      void save() const;

   public:
      // 3 Argument Constructor: Initializes formatting but is "empty"
      Stats(unsigned columnWidth = 15, unsigned noOfColumns = 4, unsigned precision = 2);
      // 4 Argument Constructor: Initializes formatting and loads data from file
      Stats(const char* filename, unsigned columnWidth = 15, unsigned noOfColumns = 4, unsigned precision = 2);
      
      // Copy Constructor: Performs deep copy and creates a "C_" prefixed file
      Stats(const Stats& other);
      // Copy Assignment: Overwrites target file with source data and performs deep copy
      Stats& operator=(const Stats& other);
      // Destructor: Cleans up dynamic memory
      ~Stats();

      // Sorts numbers in Ascending or Descending order
      void sort(bool ascending);
      // Returns number of elements
      unsigned size()const;
      // Returns the filename
      const char* name()const;
      // Displays numbers in a range and returns the count of occurrences
      unsigned occurrence(double min, double max, std::ostream& ostr = std::cout);

      // Index operator: allows array-like access with "loop-back" logic
      double& operator[](unsigned idx);
      // Const Index operator: allows read-only access with "loop-back" logic
      double operator[](unsigned idx)const;
      // Boolean conversion: true if object is not empty
      operator bool()const;

      // Helper Operators
      friend std::ostream& operator<<(std::ostream& os, const Stats& S);
      friend std::istream& operator>>(std::istream& is, Stats& S);
   };
}
#endif