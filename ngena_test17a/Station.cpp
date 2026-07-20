#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca
{
    size_t Station::m_widthField = 1;
    int Station::id_generator = 0;

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
    Station::Station(const std::string& line)
    {
        m_id = ++id_generator;
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        // Parse record parameters sequentially
        m_itemName = util.extractToken(line, next_pos, more);
        if (more) {
            m_serialNumber = std::stoul(util.extractToken(line, next_pos, more));
        }
        if (more) {
            m_quantity = std::stoul(util.extractToken(line, next_pos, more));
        }
        
        // Dynamically adjust the static width shared across all stations
        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }
        
        if (more) {
            m_itemDesc = util.extractToken(line, next_pos, more);
        }
    }

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
    void Station::display(std::ostream& os, bool full) const
    {
        // ID: 3 digits zero padded
        os << std::setw(3) << std::setfill('0') << m_id << " | ";
        
        // Item Name padded by maximum field width calculated
        os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << " | ";
        
        // Serial Number: 6 digits zero padded
        os << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

        if (full) {
            os << " " << std::setw(3) << std::setfill(' ') << m_quantity << " | " << m_itemDesc;
        }

        
        // std::setw(1)
        os << std::endl;
    }
}