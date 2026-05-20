#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>
#include <string>
#include <chrono>

namespace seneca {
    /////////////////////////////////////////
        //Stores info about a single event that
        // happended during execution of program
        ////////////////////////////////////////
    class Event {
        std::string m_eventName{};
        std::chrono::nanoseconds m_duration{ 0 };
    public:
        Event() = default; //= default()???
        //////////////////////////////////////////////////
        // Instantiates the current instance with
        // the values of the parameters
        //////////////////////////////////////////////////
        //no need fo rule of 3/5? no dma?
        Event(const char* name, const std::nanosecond& duration);
        /*******************************************
        * -> Friend Helper operator<<
        * ->inserts into the first parameter an object
        * of type Event received as the parameter, using
        * the format:
        * Counter: EVENT_NAME -> DURATION TIME_UNITS
        *********************************************/
        friend std::ostream& operator<<(std::ostream& os, const Event& event);

    }
}
#endif