#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <string>
#include <iostream>
#include "CustomerOrder.h"
#include "Workstation.h"



namespace seneca 
{
    /********************************************************
    * The LineManager class manages an assmbly line of active
    * stations
    *********************************************************/
    class LineManager
    { 
        
        //instance variables: 

        ////////////////////////////////////////////
        //The collection of
        // workstations for current assembly line
        ///////////////////////////////////////////////
        std::vector<Workstation*> m_activeLine;

        size_t m_cntCustomerOrder; //the total number of customer objects

        //points to the first active station on the current line
        Workstation* m_firstStation;

        //Member functions...

        /************************************************************************************
        * This constructor receives the name of the file that identifies the active stations
        * on the assembly line (example AssemblyLine.txt) and the collection of woekstations 
        * available to configuring the assembly line
        * 
        * The file contains the linkage between workstation pairs.
        * The format of each record in the file is WORKSTATION|NEXT_WORKSTATION
        * The records themselves are not in any particular order
        * 
        * This function stores the workstation in the order received from the file in the
        * m_activeLine instance variable. It loads the contents of the file, stores the address
        * of the next workstation in each element of the collection, identifies the first station in
        * the assembly line and stores its address in the m_firstStation attribute.
        * This function also updates the attribute that holds the total number of orders in the
        * g_pending queue. If something goes wrong, this constructor reports an error.
        * 
        * NOTE: use STL algorithms throughout this function, except for iterating through the
        * file records (one while loop); DO NOT USE for, while or do-while loops
        * except for iterating the file records
        *************************************************************************************/
        LineManager(const std::string&file, const std::vector<Workstation*>& stations);

        /***************************************************************
        * This modifier reorders the workstations present in the instance
        * varible m_activeLine (loaded by the constructor) and stores the
        * reordered collection in the same instance variable. The elements
        * in the reordered collection start with the first station, proceeds
        * to the next, and so forth untill the end of the line.
        ****************************************************************/
       void reorderStations();

       /**********************************************************
       * the modifier performs ONE iteration of operations on all
       * of the workstations in the current assembly line by doing 
       * the following:
       * - keeps track of the current iteration number [use local variable]
       * - inserts into stream os the iteration number (how many times this
       * function has been called by the client) in the formrat:
       *    Line Manager Iteration: COUNT<endl>
       * - moves order at the front of g_pending queue to the m_firstStation
       * and remove it from the queue. This function moves only one order to
       * to the line on a single iteration
       * - for each station on the line, executes one fill operation
       * - for each station on the line, attempts to move an order down the line
       * return true if all customer orders have been filled or cannot be filled,
       * otherwise returns false
       ***********************************************************/
      bool run(std::ostream);

      //this query all active stations on the assembly line
      //in their current order
      void display(std::ostream& os) const;

    };

}
#endif