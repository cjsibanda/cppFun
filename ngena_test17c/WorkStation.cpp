#include <iostream>
#include <string>
#include <utility>
#include "Workstation.h"

namespace seneca
{

    //global queues
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string& record)
       : Station(record)
    {

    }

    //modifier that fills the order at the front of the queue if
    //there are CustomerOrders in the queue: otherwise, does nothing
    void Workstation::fill(std::ostream& os)
    {
       if (!m_orders.empty())
       {
        m_orders.front().fillItem(*this, os);
       }
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
        if (m_orders.empty())
        {
            return false;
        }        

        bool moved = false;
        CustomerOrder& order = m_orders.front();

        //If orders is complete for station OR cannot be filled
        if (order.isItemFilled(getItemName()) || getQuantity() == 0)
        {
            if (m_pNextStation)
            {
                *m_pNextStation += std::move(order);
            }
            else{
                if (order.isOrderFilled())
                {
                    g_completed.push_back(std::move(order));
                }
                else
                {
                   g_incomplete.push_back(std::move(order));
                }
            }

            m_orders.pop_front();
            moved = true;
        }

        return moved;
    }

    //---------------------------------------------------------------
    // this modifier stores the address if the referenced WorkStation
    // object in the pointer to the m_pNextStation. Parameter default
    // to nullptr
    //---------------------------------------------------------------
    void Workstation::setNextStation(Workstation* station)
    {
       m_pNextStation = station;
    }

    //this query returns the address of the next WorkStation
    Workstation* Workstation::getNextStation() const
    {
       return m_pNextStation;
    }

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
        os << getItemName()
           << " --> ";


        if (m_pNextStation)
        {
            os << m_pNextStation->getItemName();
        }
        else
        {
            os << "End of Line";
        }


        os << std::endl;
    }

    //this moves the CustomerOrder reference in parameter
    // newOrder to the back of the queue
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}