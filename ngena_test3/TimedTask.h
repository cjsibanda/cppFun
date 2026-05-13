//Copy and Move Semantics
#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <chrono>
#include <string>

namespace seneca 
{
    constexpr int MAX_EVENTS = 10;
    /************************************************
    * - TimedTask manages a statically-allocated
    * array of task objects
    * - the class predifines the maximum number of
    * event onjects at 10
    * documentation for std::chrono::steady_clock is at:
    * https://en.cppreference.com/w/cpp/chrono/time_point
    * - documentation for duration of class is here:
    * https://en.cppreference.com/w/cpp/chrono/duration
    * - The friend insertion op receices a reference to
    * an std::ostream object and a TimedTask object
    * should record the arrat in the following format:
    *
    *      Execution Times:
    *      --------------------------
    *      TASK_NAME DURATION UNITS
    *      TASK_NAME DURATION UNITS
    *      ...
    *      --------------------------
    *
    **************************************************/
    class TimedTask {
        int m_count{ 0 };
        std::chrono::steady_clock::time_point m_startingTime;
        std::chrono::steady_clock:;time_point m_endingTime;
        // array of type structure
        struct Task {
            std::string m_name{};
            std::string m_unitOfTime{};
            std::string m_durationOfTime{};
        }         m_events[MAX_EVENTS];
    public:
        void startClock();
        void stopClock();
        /////////////////////////////////////////////////////
        // addTask() is a modifier that receives the address 
        // that holds the name of the task
        // it will updaten the next time-record in the array
        /////////////////////////////////////////////////////
        void addTask(const char*);
        friend std::ostream& operator<<(std::ostream& out, const TimedTask& task);
    }

}
#endif