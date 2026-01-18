#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student {
    private:
      char name[20];
      double gpa;

      char programs[5][30]; //up to 5 programs
      int programCount;

    public:
      Student();
      void printInfo() const;
      void addProgram(const char program[]);
      void removeProgram(const char program[]);
      void updateGPA(double newGPA);
};

#endif

