#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>
#include <iostream>

namespace seneca
{
    /*********************************************************
    * Station module manages information about a station 
    * on the assembly line, which holds a specific item 
    * and fills customer needs
    **********************************************************/
    class Station
    {
        int m_id{}; //id of the station
        std::string m_itemName{}; // name of the item handled by the station
        std::string m_itemDesc{}; //description of the station
        size_t m_serialNumber{}; // the next serial number to be assigned to the station
        size_t m_quantity{}; 

        //The max number of characters required to print
        //to the screen tje item name of any object of type station
        //initial value is 0 
        static size_t m_widthField; //{0}??

        /******************************************************
        * variable used to generate IDs for new instance 
        * of type station
        * - Evrytime a new instance is created, the current
        * value of the id_generator is stored in that instance,
        * and id_generator is incremented, initial value is 0.
        *******************************************************/
        static int id_generator;

    public:
        /************************************************************
        * Custom 1-argument constructor
        * - Station object receives reference to unmodifieable std::string
        * This string contains a single record/line retreived from input file
        * - constructor uses Utilities object
        * - constructor assumes string contains 4 fields
        * in the order: name, serial number, quantity, description
        * - the toen delimiter is a single character (specified by client
        * and previously stored into the Utilities class of objects)
        * - before extrating description, it updates Station::m_widthField
        * to max value of Station::m_widthField and Utilities::m_widthField
        * NOTE: display function uses this field width to
        * align the output across all the records retrieved from file
        *************************************************************/
        Station(const std::string& line);

        //returns the name of the current Station Object
        const std::string& getItemName() const { return m_itemName; }

        //returns the next serial number to be used on the 
        //.. assmebly line and increments m_serialNumber
        size_t getNextSerialNumber() { return m_serialNumber++; }

        //returns the remaining quantity of items in the station
        //object
        size_t getQuantity() const { return m_quantity; }

        //subtracts 1 from the availability quanyity
        // should not drop below 0 
        void updateQuantity() { if (m_quantity > 0) m_quantity--; }
 
        /*************************************************************
        * Inserts information about the current object into stream os
        * - if second id is false, function inserts only ID, name, serial
        * in format: ID | NAME | SERIAL
        * - if second param is true, function inserts info in the 
        * format: ID | NAME | SERIAL | QUANTITY | DESCRIPTION
        * the ID field uses 3 characters, the NAME field uses w_widthField
        * characters, QUANTITY field uses 4 characters, the SERIAL field
        * uses 6 characters; the DESCRIPTION has no formatiing options
        * - the function terminates the printed message with an endline
        **************************************************************/
        void display(std::ostream& os, bool full) const;
    };
}
#endif