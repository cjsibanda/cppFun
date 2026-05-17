#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <iostream>
#include <string>

namespace seneca
{
    /******************************************************
    * -> manages dynamically allocated collection of events
    * ... in the form of an array
    * -> at minimum it should store the address of array
    * -> should also add any private members
    *... that your design requires
    ** !! Class DOES NOT support copy ops
    ******************************************************/
    class Logger {
      int something; //??
    public:
      Logger();
      ~Logger();
      //Move ops
      ///////////////////////////////////////////////////////
      // -> addEvent should add to the array a copy of
      // the event received as a parameter
      ///////////////////////////////////////////////////////
      void addEvent(const Event& event);
      //friend helper operator

    }
}
#endif