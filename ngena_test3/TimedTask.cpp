//Copy & Move Semantics

#include <iomanip>
#include "TimedTask.h"

namespace seneca {
    
    /***********************************
    * Start the timer
    * void TimedTask::startClock()
    ************************************/
    void TimedTask::startClock()
    {
        m_startingTime = std::chrono::steady_clock::now();
    }

    /***************************************
    * Stop Timer
    * void TimedTask::stopClock()
    ****************************************/
    void TimedTask::stopClock()
    {
        m_endingTime = std::chrono::steady_clock::now();
    }

    /*****************************************
    * Record the event
    * receives the address of a C-style null terminated string
    that holds the name of the task
    * Function will update the next time-record in array
    * stores into the name attribute the C-style string reveived as parameter
    * void TimedTask::addTask(const char* msg)
    *******************************************/
    void TimedTask::addTask(const char* msg)
    {
        auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endingTime - m_startingTime );
        if (m_count < MAX_EVENTS)
        {
            this->m_events[m_cnt].m_description = msg;
            this->m_events[m_cnt].m_unitOfTime = "nanoseconds";
            this->m_events[m_cnt].m_durationOfTime = ms;
            m_cnt++;
        }

        /////////////////////////////
    }

    /*******************************************************************
    * ->friend insertion op
    * ->receives reference to std::ostream object and a TimedTask object
    * ->The operator recoreds from array in the following format
    *
    *
    *       Execution Times:
    *       --------------------------
    *        TASK_NAME DURATION UNITS
    *        TASK_NAME DURATION UNITS
    *        ...
    *        --------------------------
    * 
    * -> name of task should be in a field of size 21
    * -> it should be aligned on the left
    * -> the duration should be in a flied of size 13 
    * std::ostream& operator<<(std::ostream& out, const TimedTask& task)
    *******************************************************************/
    std::ostream& operator<<(std::ostream& out, const TimedTask& task)
    {
        out << "------------------------\n";
        out << "Execution Times:\n";
        out << "-------------------------\n";
        for (int i = 0; i < task.m_count; i++)
              out << std::setw(21) << std::left
                << task.m_events[i].m_name << ' ' << std::setw(13) << std::right
                << task.m_events[i].m_durationOfTime.count() << ' '
                << task.m_events[i].m_unitOfTime << '\n';
              out << "---------------------\n";
              return out;
    }

    /////////////////////////////////////////////////////////////////
    // std::chrono::steady::steady_clock::now() documentation here...
    // https://en.cppreference.com/cpp/chrono/steady_clock/now
    ///////////////////////////////////////////////////////////////////



}