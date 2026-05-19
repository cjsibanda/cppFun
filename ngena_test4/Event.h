#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>

namespace seneca {
    class Event {
        std::string* m_eventName{ nullptr };
        /////////////////////////////////////////
        //Stores info about a single event that
        // happended during execution of program
        ////////////////////////////////////////
    public:
        Event();
        //////////////////////////////////////////////////
        // Instantiates the current instance with
        // the values of the parameters
        //////////////////////////////////////////////////
        Event(const char* name, const std::nanosecond& duration);
        Event(const Event&);
        Event(Event&&) noexcept;
        Event& operator=(const Event&);
        Event& operator=(Event&&) noexcept;
        ~Event()
        /*******************************************
        * -> Friend Helper operator<<
        * ->inserts into the first parameter an object
        * of type Event received as the parameter, using
        * the format:
        * Counter: EVENT_NAME -> DURATION TIME_UNITS
        *********************************************/
        friend std::ostream& operator<<(std::ostream out, const Event& event);

    }
}