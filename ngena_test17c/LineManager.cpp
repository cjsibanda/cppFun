#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

#include "Station.h"
#include "LineManager.h"

namespace seneca
{
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
        LineManager::LineManager(const std::string& file,
                    const std::vector<Workstation*>& stations
                )
                {

                   std::ifstream fin(file);
                   if (!fin)
                   {
                      throw std::string("Unable to open file: ") + file;
                   }

                 std::string record;



                 while (std::getline(fin, record))
                 {

                    size_t pos = record.find('|');

                    std::string current =
                     record.substr(0, pos);

                    auto currentWS =
                     std::find_if(
                      stations.begin(),
                      stations.end(),
                       [&](Workstation* ws)
                       {
                         return ws->getItemName() == current;
                       }
                     );

                    if (currentWS != stations.end())
                    {
                      m_activeLine.push_back(*currentWS);

                    if (pos != std::string::npos)
                    {

                      std::string next =
                      record.substr(pos + 1);

                      auto nextWS =
                        std::find_if(
                          stations.begin(),
                          stations.end(),
                           [&](Workstation* ws)
                          {
                             return ws->getItemName() == next;
                          }
                       );

                    if (nextWS != stations.end())
                    {
                      (*currentWS)->setNextStation(*nextWS);
                    }
 
               }
           }
         }


             // find first station
             auto first = std::find_if(
               m_activeLine.begin(),
               m_activeLine.end(),
                [&](Workstation* ws)
              {

                return std::none_of(
                   m_activeLine.begin(),
                   m_activeLine.end(),
                    [&](Workstation* other)
                   {
                      return other->getNextStation() == ws;
                   }
               );

            }
         );


         if (first != m_activeLine.end())
         {
           m_firstStation = *first;
         }

          m_cntCustomerOrder = g_pending.size();
      }

        /***************************************************************
        * This modifier reorders the workstations present in the instance
        * varible m_activeLine (loaded by the constructor) and stores the
        * reordered collection in the same instance variable. The elements
        * in the reordered collection start with the first station, proceeds
        * to the next, and so forth untill the end of the line.
        ****************************************************************/
       void LineManager::reorderStations()
       {
          std::vector<Workstation*> ordered;
          
          Workstation* current = m_firstStation;

          while(current)
          {
            ordered.push_back(current);
            current=current->getNextStation();
          }

          m_activeLine=ordered;

       }

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
      bool LineManager::run(std::ostream& os)
      {
         static size_t iteration = 0;


         os << "Line Manager Iteration: "
            << ++iteration
            << std::endl;

         if(!g_pending.empty() && m_firstStation)
         {
             *m_firstStation += std::move(g_pending.front());
             g_pending.pop_front();
         }

         std::for_each(
             m_activeLine.begin(),
             m_activeLine.end(),
             [&](Workstation* ws)
             {
                 ws->fill(os);
             }
         );

         std::for_each(
             m_activeLine.begin(),
             m_activeLine.end(),
             [&](Workstation* ws)
             {
                 ws->attemptToMoveOrder();
             }
         );

         return
            g_completed.size()+g_incomplete.size()
            ==
            m_cntCustomerOrder;
        }

      //this query all active stations on the assembly line
      //in their current order
      void LineManager::display(std::ostream& os) const
      {
             std::for_each(
             m_activeLine.begin(),
             m_activeLine.end(),
             [&](Workstation* ws)
             {
                 ws->display(os);
             }
         );

     }
 }
    
//}