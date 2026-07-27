#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <thread>
#include "Workstation.h"

namespace seneca
{
    //modifier that fills the order at the front of the queue if
    //there are CustomerOrders in the queue: otherwise, does nothing
    void Workstation::fill(std::ostream& os)
    {
       //
    }

    /*********************************************************
    * - Attempts to move the order at the front of the queue
    * - to the next station in the assembly line:
    * - if the order requires no more service at this station
    * or cannot be filled (not enough inventory), move it to 
    * the next station; otherwise do nothing
    * - If there is no next station in the assembly line, then
    * the order is moved into g_completed or g_incomplete queue
    * - if an order has been moved, return true; false otherwise
    *************************************************************/
    bool Workstation::attemptToMoveOrder()
    {
        //
    }

    //---------------------------------------------------------------
    // this modifier stores the address if the referenced WorkStation
    // object in the pointer to the m_pNextStation. Parameter default
    // to nullptr
    //---------------------------------------------------------------
    void Workstation::setNextStation(WorkStation* station)
    {
       //
    }

    //this query returns the address of the next WorkStation
    Workstation* getNextStation() const;

    /*******************************************************
    * this query inserts the name of the Item for which the 
    * current object is responsible into stream os following the format:
    * ITEM_NAME --> NEXT_ITEM_NAME
    * -- if the current object is the last Workstation in the 
    * assembly line this query inserts:
    * ITEM_NAME --> End of Line
    * -- in either case, the message is terminate with \n
    ********************************************************/
    void Workstation::display(std::ostream& os) const
    {
       //
    }

    //this moves the CustomerOrder reference in parameter
    // newOrder to the back of the queue
    Workstation& Workstation::operator+=(Customer&& newOrder)
    {
        //
    }
}