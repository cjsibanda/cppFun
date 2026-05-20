//m_count -> is the counter
#include <iomanip>
#include "Event.h"
#include "Settings.h"


namespace seneca {
    
    Event::Event(const char* name, const std::chrono::nanoseconds& duration) {
        if (name && name[0] != '\0') {
           m_eventName = name;
        }
        m_duration = duration;
    }

    /***********************************************
    * friend helper operator operator<<
    * -> inserts the first parameter an object of type Event
    * received as the second parameter
    * Format:
    * counter: EVENT_NAME -> DURATION TIME_UNITS
    * [COUNTER] : right aligned field of size 2
    *           : holds number of times op is called
    * EVENT_NAME: right aligned field of size 40
    *           : name of event
    * [DURATION]: right aligned field with duration of event
    *           : size depends on the time units stored in global settings  
    *
    ************************************************/
    std::ostream& operator<<(std::ostream& os, const Event& event) {
        /************************************************ 
        * static size_t is a local-to-function variable
        * it persists for the program's lifetime
        *************************************************/
        static size_t m_count = 0;
        m_count++;

        //////////////////////////////////////////////////
        //Read formatting requirements for global settings
        ///////////////////////////////////////////////////
        std::string units = g_settings.m_time_units;
        double displayTime = 0.0;
        int fieldWidth = 11; //Default width for nanoseconds

        if (units == "seconds") {
            displayTime = event.m_duration.count() / 1000000000.0;
            fieldWidth = 2;
        } else if (units == "milliseconds") {
            displayTime = event.m_duration.count() / 1000000.0;
            fieldWidth = 5;
        } else if (units == "microservices") {
            displayTime = event.m_duration.count() / 1000.0;
            fieldWidth = 8;
        } else { //nanoseconds
            displayTime = static_cast<double>(event.m_duration.count());
            fieldWidth = 11;
        }

        //Format: COUNTER: EVENT_NAME -> DURATION TIME_UNITS
        os << std::setw(2) << std::right << m_count << ": "
           << std::setw(40) << std::right << event.m_eventName << " -> "
           << std::setw(fieldWidth) << std::right << displayTime << " " << units;

           return os;

    }
    
}
