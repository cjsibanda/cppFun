#ifndef SENECA_SET_H
#define SENECA_SET_H
#include <cmath>  //for std::fabs()
#include "Collection.h"

namespace seneca {
    //Set represents a collection where no
    //item appears more than once
    template<typename T>
    class Set : public Collection<T, 100>
    {
       //private members???
    public:
       //overriding the inherited function here
       bool add (const T& item) override
       {
         for (unsigned int i = 0; i < this->size(); ++i)
         {
            if ((*this)[i] == item)
                      return false;
         }

         return Collection<T, 100>::add(item);
       }

    };

    /////////////////////////////////////////
    //The specialization for double...
    //numbers that are 0.01 from each other
    //are considered the same
    template<>
    inline bool Set<double>::add(const double& item) {
      const double epsilon = 0.01;
      
      for (unsigned int i = 0; i < this->size(); ++i) {
         if (std::fabs((*this)[i] - item) <= epsilon) {
            return false;
         }
      }
      return Collection<double, 100>::add(item);

    }
    
}
#endif