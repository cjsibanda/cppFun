#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

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
        void size();  //fix
        void display(); //fix
        bool add(const T& item); //fix
        //operator[];
        virtual ~Collection() = default; //okay? 
    };

    // Template Assumptions here
    template<typename T, int CAPACITY>
    //....

    template<>
    //....
}
#endif

//is there need for .cpp file?? .. why not?