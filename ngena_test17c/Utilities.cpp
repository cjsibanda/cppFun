#include <stdexcept>
#include "Utilities.h"


namespace seneca
{
    /******************************************************
    * separates the tokens in any given 
    * std::string object. All Utilities objects in the
    * system share the same delimiter. 
    ******************************************************/
    char Utilities::m_delimiter = ',';

    /*********************************************************************
        * extracts a token from string str referred to
        * by the first parameter.
        * 
        * This function:
        * - uses the delimiter to 
        * extract the next token from 
        *  starting at position next_pos
        * - If successful, return a copy of the extracted token
        * found (without spaces at the beginning/end), update next_pos
        * with the position of the next token, and set more to true (false otherwise).
        * reports an exception if a delimiter is found at next_pos
        * - updates the current object's m_widthField data member if its
        * current value is less than the token extracted
        * 
        * NOTE: in this application: str represents a single line that
        * has been read from an input file
        **************************************************************************/
        std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        if (next_pos >= str.length()) {
            more = false;
            return "";
        }

        // Exception check: if delimiter is directly at next_pos
        if (str[next_pos] == m_delimiter) {
            more = false;
            throw std::runtime_error("No token found at index.");
        }

        size_t delim_pos = str.find(m_delimiter, next_pos);
        std::string token;

        if (delim_pos == std::string::npos) {
            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        } else {
            token = str.substr(next_pos, delim_pos - next_pos);
            next_pos = delim_pos + 1;
            more = true;
        }

        // Manual whitespace trimming (front and back)
        size_t first = token.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) {
            token = "";
        } else {
            size_t last = token.find_last_not_of(" \t\r\n");
            token = token.substr(first, (last - first + 1));
        }

        // Update the instance field width if this token is larger
        if (token.length() > m_widthField) {
            m_widthField = token.length();
        }

        return token;
    }

    //Class Function in Header file
       
       

}