#ifndef SENECA_PAIR_H
#define SENECA_PAIR_H

#include <iostream>
#include <string>

namespace seneca {

  
  /************************************************
  * -> the pair module represents a value-key pair
  * -> 2 objects of type Pair are considered equal if..
  * .. if they have same key
  * [QUESTION]: why is it important to add each
  * one of the members you have decided to add
  *************************************************/
  class Pair 
  {
    std::string m_key{};
    std::string m_value{};
  public:
    const std::string& getKey() { return m_key; }
    const std::string& getValue() {return m_value; }
    Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{}
    
    /////////////////////////////////////////////
    // add any other prototypes for members here
    //////////////////////////////////////////////
    Pair() = default;
    bool operator==(const Pair& src);
    friend std::ostream& operator<<(std::ostream& out, const Pair& item);
  }

}

#endif