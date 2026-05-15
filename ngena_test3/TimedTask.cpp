//Copy & Move Semantics

#include <iomanip>
#include "TimedTask.h"

namespace seneca {
    
    /***********************************
    * Start the timer
    * void TimedTask::startClock()
    ************************************/

    /***************************************
    * Stop Timer
    * void TimedTask::stopClock()
    ****************************************/

    /*****************************************
    * Record the event
    * receives the address of a C-style null terminated string
    that holds the name of the task
    * Function will update the next time-record in array
    * stores into the name attribute the C-style string reveived as parameter
    * void TimedTask::addTask(const char* msg)
    *******************************************/

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
    
    /////////////////////////////////////////////////////////////////
    // std::chrono::steady::steady_clock::now() documentation here...
    // https://en.cppreference.com/cpp/chrono/steady_clock/now
    ///////////////////////////////////////////////////////////////////



}