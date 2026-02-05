// ref 12

#include <iostream>
using namespace std;
#include <cstring>

#include "GraftA.h"

namespace igwijo {
    void Graft::set(long id, const char* firstName, const char* lastName) {
      workerID = id;
      strcpy(workerFirstName,firstName);
      strcpy(workerLastName, lastName);    
    }

    void Graft::print() const {
        cout << endl << "The Worker's ID: " << workerID << endl
           << "The Worker's Name: " << workerFirstName << " " << workerLastName << endl;
    }

    void printTheWorker(const Graft& busyBee) {
        busyBee.print();
    }

    void setTheWorker(Graft& busyBee, long id, const char* firstName, const char* lastName) {
       busyBee.set(id, firstName, lastName);
    }
}