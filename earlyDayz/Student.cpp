#include "Student.h"
#include <cstring> //for strcpy and strcmp

using namespace std;

//Constructor
Student::Student() {
    strcpy(name, "Greg");
    gpa = 0.0;
    programCount = 0;
}

//Print student information
void Student::printInfo() const {
    cout << "Name:" << name << endl;
    cout << "GPA:" << gpa << endl;
    cout << "Programs:";

    if (programCount == 0) {
        cout << "None";
    } else {
        for (int i = 0; i < programCount; i++) {
            cout << programs[i] << "";
        }
    }
    cout << endl;
}

//Add a program
void Student::addProgram(const char program[]) {
    if (programCount < 5) {
        strcpy(programs[programCount], program);
        programCount++;
    }
}

//Remove a program
void Student::removeProgram(const char program[]) {
    for (int i = 0; i < programCount; i++) {
        if(strcmp(programs[i],program) == 0) {
            for (int j = i; j < programCount - 1; j++) {
                strcpy(programs[j], programs[j + 1]);
            }
            programCount--;
            break;
        }
    }
}

//Update GPA
void Student::updateGPA(double newGPA){
    gpa = newGPA;
}