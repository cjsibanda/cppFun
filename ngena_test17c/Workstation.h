#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <string>
#include <iostream>
#include "CustomerOrder.h"

namespace seneca 
{
    /*******************************************
    * The workstation class defines the structure
    * of an active station on assembly line.
    * Each Workstation is-a-kind-of Station.
    * Workstation object cannot be copied or moved
    ***********************************************/
    class WorkStation
    { 
        /*****************************
        * Though it cost all you have
        *  ... get understanding
        *******************************/
       std::vector<Workstation*> m_activeLine //the collection of workstations for assembly line
       size_t m_cntCustomerOrder; //the total number of CustomerOrder objects
       Workstation* m_firstStation; //points to the first active station on the current line
        
    }

}
#endif