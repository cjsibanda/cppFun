#include <iostream>
#include "NameTag.h"
using namespace std;

namespace shibobo {
    void NameTag::set(const char* name) {
        int i = 0;
        for (; name && name[i] && i < 50; i++) {
            m_name[i] = name[i];
        }
        m_name[i] = 0;
        m_width = i;
    }

    void NameTag::setWidth(int width) {
        m_width = width;
    }

    void NameTage::printLine() const {
        for (int i = 0; i < m_width + 4; i++) {
            cout << "*";
        }
        cout << endl;
    }

    void NameTag::print() const {
        printLine();
        cout << "* ";
        cout << m_name;
        for (int i = length(); i < m_width; i++) {
            cout << " ";
        }
        cout << " *" << endl;
        printline();
    }
}