#include "Student.h"
#include <iostream>

using namespace std;

int main() {
    Student greg;

    greg.printInfo();
    cout << endl;

    greg.addProgram("Computer Science");
    greg.addProgram("Mathematics");
    greg.updateGPA(3.5);

    greg.printInfo();
    cout << endl;

    greg.removeProgram("Mathematics");
    greg.printInfo();

    return 0;
}