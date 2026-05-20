#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <iostream>
#include <chrono>
#include <string>
#include "Event.h"

namespace seneca
{
    /****************************************************** 
    * -> Measures the duration of various operations/events
    * -> Should use chrono library for timed related ops
    *******************************************************/
    class TimeMonitor 
    {
      std::string m_event_name{};
      std::chrono::steady_clock::time_point m_start_time{}; 
    public:
      /******************************************
      * -> a new event with the name starts
      * -> records the time when the event started 
      * and the name of the event
      ******************************************/
      void startEvent(const char* name);
      /**********************************
      * -> take the time when the event has ended
      * -> calulates the duration of the event
      * -> create an instance of type Event and return to client
      ***********************************/
      Event stopEvent();  

    };
}
#endif