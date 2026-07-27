#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <vector>
#include <string>
#include "Station.h"

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
              Item(const std::string& src) : m_itemName{src} {}; 
           };
    /********************************************************
    * CustomerOrder contains all the functionality for
    * processing customer orders as they move from Station
    * to Station along the assembly line. The Station where a
    * given order currently rests fills a requests for one item
    * of that station.
    ***********************************************************/
    class CustomerOrder
    {
          //Instance variables
          std::string m_name; ///name of the customer
          std::string m_product; //name of the product being assembled
          size_t m_cntItem; //a count of the number of items in the customer's order
          /********************************************************
          * A dynamically allocated array of pointers. Each element
          * of the array points to dynamically allocated object of 
          * type Item. This is the Resource that your class MUST manage 
          **********************************************************/
          Item** m_listItem{nullptr};
          
          //The maximum width of a field, used for display
          static size_t m_widthField;

       public:
          //default constructor
          CustomerOrder() = default;

          /******************************************************
          * A customer 1-argument constructor that takes a
          * reference to an unmodifiable string. This constructor
          * uses a local Utilities object to extract the tokens from
          * the string and populate the current instance. The field
          * in the strings are
          * -> Customer Name
          * -> Order Name
          * -> the list of items making up the order (at least on item)
          * After finishing extraction, this constructor updates 
          * CustomerORder::m_widthField if the current value is smaller
          * that the value stored in Utilities::m_widthField
          ********************************************************/
          CustomerOrder(const std::string& record);

          // Copy operations are disallowed
          //The copy constructor should throw an exception if called
          CustomerOrder(const CustomerOrder& other) {
            throw std::runtime_error("Copy operations are not allowed.");
         }
         CustomerOrder& operator=(const CustomerOrder& other) = delete;


         // Move operations must promise no that it doesn't throw exceptions
         //noexcept
         CustomerOrder(CustomerOrder&& other) noexcept;
         CustomerOrder& operator=(CustomerOrder&& other) noexcept;
 
         //destructor
         ~CustomerOrder();

         //returns true if all items in the order have been filled
         bool isOrderFilled() const;
         //returns true if all items specified by itemName have been filled
         //If the item doesn't exist in the order, this query returns true
         bool isItemFilled(const std::string& itemName) const;
         /*******************************************************
         * This modifier fills one item in the current order that
         * the Station specified in the first parameter handles
         * - if the order doesn't contain the item handled, 
         * this function does nothing
         * - If the order contains items handled, and the 
         * Station's inventory contains at least one item, 
         * this function fills the order with one single item.
         *  It subtracts 1 from the inventory and updates 
         * Item::m_serialNumber and Item::m_isFilled. I
         * t also prints the message     
         * Filled NAME, PRODUCT [ITEM_NAME].
         * 
         * - if the order contains items handled but unfilled, 
         * and the inventory is empty, this function prints the
         *  message     Unable to fill NAME, PRODUCT [ITEM_NAME].
         * - all messages printed are terminated by an endline
         ********************************************************/
         void fillItem(Station& station, std::ostream& os);

         /*********************************************************
         * this query displays the state of the current object
         * 
         * CUSTOMER_NAME - PRODUCT
         * [SERIAL] ITEM_NAME - STATUS
         * [SERIAL] ITEM_NAME - STATUS
         * ...
         * 
         * SERIAL - a field of width 6
         * ITEM_NAME - a field of size m_widthField
         * STATUS is either FILLED or TO BE FILLED
         * you must use IO manipulators to format this output
         **********************************************************/
         void display(std::ostream& os) const;
           
    };
}
#endif