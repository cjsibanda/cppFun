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
    class Collection {
        //private memebers
        // an object of type T stat store default value
    public: 
        void size();
        void display();
        bool add(const T& item);
        //operator[];
        virtual ~Collection(); 
    }
};
#endif