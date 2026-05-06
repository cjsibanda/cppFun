#include <iostream>
#include "Pair.h"

namespace sibanda 
{
    bool Pair::operator==(const Pair& other)
    {
        return this->m_key == other.m_key;
    }

    std::ostream& operator<<(std::ostream& out, const Pair& item)
    {
        out << std::setw(20) << item.m_key << ": " << item.m_value;
        return out;
    }
}