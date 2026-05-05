// template classes
// specializing a templated class variable for a particular type
//
#ifndef SIBANDA_COLLECTION_H
#define SIBANDA_COLLECTION_H
#include <iostream>
#include "Pair.h" //add later, won't work for now

namespace sibanda
{
  // --> T= type of any element in the collection
  // --> CAPACITY is the max nummber of elements tahat can be added to the collection

  template <typename T, int CAPACITY>
  class Collection
  {
    T m_items[CAPACITY]{};
    size_t m_noOfItems{};
    //can add private members that design requires

    //////////////////////////////////////////////////////////////////////////////////
    // --> a object of type T stat that stors the default value of collection element
    // --> returned by member functions when client requests object that doesn't exist
    /////////////////////////////////////////////////////////////////////////////////
    static T m_defaultValue; 

  public:
    ////////////////////////////////////////////////////////////////////
    // -> a mutator that adds a copy of parameter to collection 
    // if added it returns true, false otherwise
    //////////////////////////////////////////////////////////////////
    virtual bool add(const T& item) 
    {
        if (m_noOfItems < CAPACITY) 
        {
            m_items[m_noOfItems++] = item;
            return true;
        }
        return false;
    }

    //a query that returns the current number of element in the collection
    size_t size() const  
    {
        
        return m_noOfItems;
    }

    /////////////////////////////////////////////////////////////////////
    // -> recieces output stream as parameter
    // -> defualt value is std::cout
    // -> it inserts all collection items into the stream
    /////////////////////////////////////////////////////////////////////
    void display(std::ostream& out = std::cout) const
    {
        std::cout << "----------------------\n";
        std::cout << "| Collection Content |\n";
        std::cout << "----------------------\n";

        for (auto i = 0u; i < m_noOfItems; ++i)
            out << m_items[i] << '\n';
        std::cout << "------------------------\n";
    }

    /////////////////////////////////////////////////////////////////////
    // -> a query that receives index (idx) as parameter
    // -> returns a copy of the collection element stored at that index
    // -> returns default object if the index is no valid
    /////////////////////////////////////////////////////////////////////
    T operator[](size_t idx) const
    {
        if (idx < m_noOfItems)
            return m_items[idx];

        return m_defaultValue;
    }
    
    //Destructor with inclusion polymorphism enabled
    virtual ~Collection() = default;

  };

  //helps
  template<typename T, int CAPACITY>
  inline T Collection<T, CAPACITY>::m_defaultValue{};

  template<>
  inline Pair Collection<Pair, 100>::m_defaultValue("No Key", "No Value");

}
#endif