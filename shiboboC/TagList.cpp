#include <iostream>
#include "TagList.h"
using namespace std;

namespace shibobo {

    TagList::TagList(int num) {
        m_tags = nullptr;
        m_size = 0;
        m_count = 0;

        if (num > 0) {
            m_size = num;
            m_tags = new NameTag[num];

        }
    }

    void TagList::add(const NameTag& nt) {
        if (m_count < m_size) {
            m_tags[m_count] = nt;
            m_count++;
        }
    }

    void TagList::print() const {
        int maxLen = 0;

        for (int i = 0; i < m_count; i++) {
            int len = m_tags[i].length();
            if (len > maxLen) maxLen = len;
        }

        for (int i = 0; i < m_count; i++) {
            m_tags[i].setWidth(maxLen);
            m_tags[i].print();
        }
    }

    TagList::~TagList() {
        delete[] m_tags;
    }
} 

