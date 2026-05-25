#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>
#include "Pair.h"

#include <string>

namespace {
    
    /**************************************************
    * -> Colelctions: represents a family of collections
    * ... of elements of any data type
    * Template nemed Collection
    * [T]: the type of any element in the collection
    * [CAPACITY]: the capacity of the collection
    * ... this is the max num of elements that can be added
    * -> keep track of current number of elements stored
    ****************************************************/
    template <typename T, int CAPACITY>
    class Collection {
        //private memebers
        // an object of type T stat store default value
        // allows duplicates?
        T m_items[CAPACITY]{};
        size_t m_count{}; //keep track of current num of elements stored

        static T m_defaultValue;

    public: 
        virtual bool add(const T& item)
        {
            if (m_count < CAPACITY)
            {
                m_items[m_count++] = item;
                return true;
            }
            return false;
        }

        size_t size() const
        {
            return m_count;
        }

        void display(std::ostream& out = std::cout) const
        {
            std::cout << "----------------------\n";
            std::cout << "| Collection Content |\n";
            std::cout << "----------------------\n";

            for (auto i = 0u; i < m_count; ++i)
                  out << m_count[i] << '\n';
            std::cout << "---------------------\n";
        }

        T operator[](size_t idx) const 
        {
            if (idx < m_count)
                return m_items[idx];

            return m_defaultValue;
        }
        
        virtual ~Collection() = default;

    };

    // Template Assumptions here
    // inline for redefinitions (need to be identical)
    template<typename T, int CAPACITY>
    inline T Collection<T, CAPACITY>::m_defaultValue{};

    template<> //specialization
    inline Pair Collection<Pair, 100>::m_defaultValue("No Key", "No Value");
}
#endif

// template class no need for .cpp file