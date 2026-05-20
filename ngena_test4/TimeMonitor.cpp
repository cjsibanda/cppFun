#include "TimeMonitor.h"

namespace seneca {
    void TimeMonitor::startEvent(const char* name) {
        if (name) {
            m_event_name = name;
        }
        //Captureing time-stamp
        m_start_time = std::chrono::steady_clock::now();
    }

    Event TimeMonitor::stopEvent() {
        auto end_time = std::chrono::steady_clock::now();

        //Calculate raw difference in nanoseconds
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - m_start_time);

        //construct and return the completed event record
        return Event(m_event_name.c_str(), duration);
    }
}