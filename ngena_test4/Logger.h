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
      size_t m_cnt{ 0 };
      std::string* m_eventsCollection[]; //DA events in form of an array
    public:
      //Rule of 5??
      Logger();
      Logger(const Logger&);
      Logger(Logger&&) noexcept;
      Logger& operator=(const Logger&);
      Logger& operator=(Logger&&) noexcept;

      ~Logger();
      //Move ops
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