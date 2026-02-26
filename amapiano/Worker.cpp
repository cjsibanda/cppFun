#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <cstring>

#include "Worker.h"

namespace sibanda {
    Worker::Worker() {
        *this = Employee(0, "", "", 0, nullptr);
    }

    // -->....
}