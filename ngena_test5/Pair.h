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
    /************************************* 
    * This is a comparison operator
    * it will check if the m_key strings match
    * The template has to match the word (key)
    * ... to consider it found
    **************************************/
    bool operator==(const Pair& src) const;

    ////////////////////////////////////////////////
    //helps with printing formating
    //force the key(word) into right-aligned field
    // of size 20, followed by colon and value
    //////////////////////////////////////////////////
    friend std::ostream& operator<<(std::ostream& out, const Pair& item);
  };

}

/*************************************************
 * -> Why thes members are necessary
 * -> Pair() = default; ... is necessary because
 * Template collection claases require a default 
 * constructor to initialize elements when creating
 * or resizing dynamic arrays of object
 * 
 * -> bool operator==(const Pair& src) const
 * This is the Equlaity operator. It allows
 * template search functions to look up records
 * matching only the word (m_key) while ignoring definition
 * 
 * -> operator (insertion op)
 * Insertion op allows generic template
 * print/display functions to the
 * customer Pair object
 * 
 * 
 *************************************************/

#endif