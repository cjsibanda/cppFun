#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>

#include "utilities.h"

namespace seneca
{
    //constructors???

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
         //
       }

       //CLASS FUNCTIONS...

       //sets the delimiter for this class to the character received
       static void Utilites::setDelimiter(char newDelimiter)
       {
         //
       }

       //returns the delimiter for this class
       static char Utilies::getDelimiter()
       {
        //
       }

}