#include <iomanip> //??
#include "Pair.h"

namespace seneca {

    // default constuctor --> (Pair() = default;)

    /************************************* 
    * This is a comparison operator
    * it will check if the m_key strings match
    * The template has to match the word (key)
    * ... to consider it found
    **************************************/
    bool Pair::operator==(const Pair& src) const
    {
        return this->m_key == src.m_key;
    }

    ////////////////////////////////////////////////
    //helps with printing formating
    //force the key(word) into right-aligned field
    // of size 20, followed by colon and value
    //////////////////////////////////////////////////
    std::ostream& operator<<(std::ostream& out, const Pair& item)
    {
        out << std::setw(20) << item.m_key << ": " << item.m_value;
        return out;
    }
}