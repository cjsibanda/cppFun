// 10 -> 17
#include <iostream>
using namespace std;
#include <cstring>

#include "Graft.h"

namespace igwijo {
  void Graft::set(long id, const char* firstName, const char* lastName) {
    workerID = id;
    strcpy(workerFirstName, firstName);
    strcpy(workerLastName, lastName);
  }

  void Graft::print() const {
    cout << endl << "Worker's ID: " << workerID << endl
      << "Worker's Name: " << workerFirstName << " " << workerLastName << endl;
  }

}