#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <vector>
#include <string>

namespace seneca
{
    //Need forward declaration here???<--- 
    //The CustomerOrder class has the follwowing structure
           // ^ outside the class or inside?
           struct Item
           {
              std::string m_itemName;
              size_t m_serialNumber{0};
              bool m_isFilled{false};
              Item(const std::string& src) : m_itemsName{src} {}; 
           }
    /********************************************************
    * CustomerOrder contains all the functionality for
    * processing customer orders as they move from Station
    * to Station along the assembly line. The Station where a
    * given order currently rests fills a requests for one item
    * of that station.
    ***********************************************************/
    class CustomerOrder
    {

           /****************************
           * Above All Guard Your Heart
           ****************************/
          //Instance variables
          std::string m_name; ///name of the customer
          std::string m_product; //name of the product being assembled
          size_t m_cntItem;
          Item** m_listItem;

           
    };
}
#endif