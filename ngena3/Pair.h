//templates
#ifndef SIBANDA_PAIR_H
#define SIBANDA_PAIR_H
#include <string>
#include <iomanip>

namespace sibanda
{
    /*
    -> for representing key-value pairs
    -> two objects of type Pair are considered equal if they have the same key 
    */
    
    class Pair
    {
        std::string m_key{};
        std::string m_value{};
    public:
        const std::string& getKey() {return m_key; }
        const std::string& getValue() {return m_value; }
        Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value}{};
        Pair() = default;
        bool operator==(const Pair& other);
        friend std::ostream& operator<<(std::ostream& out, const Pair& item);
        
    };
}
#endif