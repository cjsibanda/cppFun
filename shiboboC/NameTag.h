#ifndef SHIBOBO_CC_H
#define SHIBOBO_CC_H
#include <iostream>

namespace shibobo {
    class NameTag {
        char m_name[51]{};
        int m_width{};

        void printLine() const;

      public:
        void set(const char* name);
        void setWidth(int width);
        int length() const;
        void print() const;        
    };
}
#endif //!SHIBOBO_CC_H