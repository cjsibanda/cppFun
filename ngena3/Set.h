#ifndef SIBANDA_SET_H
#define SIBANDA_SET_H
include <cmath>
#include "Collection.h" //added

namespace sibanda {

    constexpr int SET_CAPACITY = 100;

    /* Set inherits from Collection
    set is a collection without duplicates (no item appears more than once)
    the set will always have a collection
    the set will always have a capacity of 100 items*/
    template<typename T>
    class Set : public Collection<T, SET_CAPACITY>
    {
    public:
       //this prevents adding an item if it alreay exists in the set
       bool add(const T& item) override
       {
         for (auto i = 0u; i < this->size(); ++i)
         {
            if ((*this)[i] == item)
                  return false;
         }

         return Collection<T, SET_CAPACITY>::add(item);
       }
    };

    template<>
    bool Set<double>::add(const double& item)
    {
        double epsilon = 0.01;

        for (auto i = 0u; i < this->size(); ++i)
        {
            /*std::fabs when implementing
            two numbers are the same if their absolute value
            is smaller or equal ti 0.01
            */
            if (std::fabs((*this)[i] - item) <= epsilon)
                return false;
        }

        return Collection<double, SET_CAPACITY>::add(item);
    }
  
}
#endif