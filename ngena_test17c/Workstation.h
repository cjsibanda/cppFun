#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <string>
#include <iostream>
#include "CustomerOrder.h"

/***********************************************************
* global variables - 3 double-ended queues of CustomerOrder
* - g_pending - holds the orders to be placed onto the assembly line
* at the first station 
* - g_completed - holds the orders that have been removed from the last
station and have been completely filled
* - g_incomplete - holds the orders that have been removed from the last station
* and could be filled completely 
* - g_incomple holds the orders that have been removed from the last station
* and could ne filled completely
****************************************************************/

namespace seneca 
{
    /*******************************************
    * The workstation class defines the structure
    * of an active station on assembly line.
    * Each Workstation is-a-kind-of Station.
    * Workstation object cannot be copied or moved
    ***********************************************/
    class Workstation
    { 
        
        //instance variables: 
        /*******************************************************
        * m_orders is a double-ended-queue with CustomerOrders 
        * entering the back and exiting the front. These are orders 
        * that have been placed on this station to receive service
        * (or already received service)
        ********************************************************/
        double  m_orders;

        //m_pNextStation - a pointer to the next Workstation on the assembly line
        Workstation* m_pNextStation;

        //Member Functions

        /************************************************************
        * Custom 1-argument constructor -- receives a reference to 
        * an unmodifiable reference to std::string and passes it to
        * the Station base class
        *************************************************************/
        Workstation(std::string& Station);

        //modifier that fills the order at the front of the queue if
        //there are CustomerOrders in the queue: otherwise, does nothing
        void fill(std::ostream& os);

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
        bool attemptToMoveOrder()

        //---------------------------------------------------------------
        // this modifier stores the address if the referenced WorkStation
        // object in the pointer to the m_pNextStation. Parameter default
        // to nullptr
        //---------------------------------------------------------------
        void setNextStation(WorkStation* station)

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
        void display(std::ostream& os) const

        //this moves the CustomerOrder reference in parameter
        // newOrder to the back of the queue
        WorkStation& operator+=(Customer&& newOrder);
    }

}
#endif