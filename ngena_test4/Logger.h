#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <iostream>
#include "Event.h"

namespace seneca
{
    /******************************************************
    * -> manages dynamically allocated collection of events
    * ... in the form of an array
    * -> at minimum it should store the address of array
    * -> should also add any private members
    *... that your design requires
    ** !! Class DOES NOT support copy ops (disable)
    ******************************************************/
    class Logger {
      size_t m_cnt{ 0 }; //is this same counter from Events?
      //std::string* m_eventsCollection[]; //DA events in form of an array
      Event* m_events{ nullptr } // which one???
    public:
      //Rule of 5??
      //no constructor?
      Logger(); // =defualt?

      //Disbale copy operations?
      Logger(const Logger&) = delete;
      Logger& operator=(const Logger&) = delete;

      //Enable move ops
      Logger(Logger&& src) noexcept;
      Logger& operator=(Logger&& src) noexcept;

      //destructor
      ~Logger();

      ///////////////////////////////////////////////////////
      // -> addEvent should add to the array a copy of
      // the event received as a parameter
      ///////////////////////////////////////////////////////
      void addEvent(const Event& event);
      /////////////////////////////////////////////////////
      //friend helper operator
      // inserts into first parameter all events stored
      // ... in the logger received as the second parameter
      //  format:
      //         EVENT<endl>
      //         EVENT<endl>
      /////////////////////////////////////////////////////
      friend std::ostream& operator<<(std::ostream, const Logger& log);
    }
}
#endif