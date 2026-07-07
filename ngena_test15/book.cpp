/*************************************************
*  It is a child who has never travelled
* who says only his mother prepares tasty meals :)
**************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

#include "book.h"
#include "settings.h"

namespace seneca {
    /***************************************************
    * class Book derived from MediaItem that can store
    * info about 
    * m_author, title, country, pub year, price, summary
    ****************************************************/
    //NOTE: This class will nit have any public constructors

    //constructors are PRIVATE!
    //add any contructors that are nessecary for design
   Book::Book(
      const std::string& author,
      const std::string& title,
      const std::string& country,
      double price,
      unsigned short year,
      const std::string& summary
   ) 
     :
     MediaItem(title, summary, year),
     m_author(author),
     m_country(country),
     m_price(price)
     {

     }

   //<------------------------------------------------------------
   // display code is provided
   // override this function to print the info about a single book
   //-------------------------------------------------------------->
   void Book::display(std::ostream& out) const
    {
      if (g_settings.m_tableView)
      {
        out << "B | ";
        out << std::left << std::setfill('.');
        out << std::setw(50) << this->getTitle() << " | ";
        out << std::right << std::setfill(' ');
        out << std::setw(2) << this->m_country << " | ";
        out << std::setw(4) << this->getYear() << " | ";
        out << std::left;
        if (g_settings.m_maxSummaryWidth > -1)
        {
          if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
            out << this->getSummary();
          else
            out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
        }
        else
          out << this->getSummary();
        out << std::endl;
      }
      else
      {
        size_t pos = 0;
        out << this->getTitle() << " [" << this->getYear() << "] [";
        out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
        out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
        while (pos < this->getSummary().size())
        {
          out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
          pos += g_settings.m_maxSummaryWidth;
        }
        out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
          << std::setfill(' ') << '\n';
      }
    }

    /*******************************************************
    * This is a class function that receives as a parameter
    * the representation of the book as a string and builds
    * a dynamically allocated object of type Book using the
    * information from the string and returns it tp the client
    * The parameter contains a single line of text extracted from
    * the file books.csv
    * Format is...
    * AUTHOR,TITLE,COUNTRY,PRICE,YEAR,SUMMARY
    * 
    * Function should remove all spaces from the beginning
    * and end of any token in the string
    * If the parameter is an empty string starting with #, 
    * ...raise an exception with the message Not a valid book
    * (lines in the file starting with # are considered comments
    * and should be ignored)
    * --> If all the data is correctly loaded, create a dynamic
    * object of type Book using your private constructors
    * and return its address to the client
    * When implemting consider these functions:
    * -- std::string::substr()
    * -- std::string::find()
    * -- std::string::string::erase()
    * -- std::stoi()
    * -- std::stod()
    *******************************************************/
    Book::Book* createItem(const std::string& strBook) 
    {
      if (strBook.empty() || strBook[0] == '#')
            throw "Not a valid book.";


        std::string tokens[6];

        size_t start = 0;
        size_t end = 0;


        for (int i = 0; i < 5; i++)
        {
            end = strBook.find(',', start);

            tokens[i] =
                strBook.substr(start, end - start);

            trim(tokens[i]);

            start = end + 1;
        }


        tokens[5] =
            strBook.substr(start);

        trim(tokens[5]);


        return new Book(
            tokens[0],
            tokens[1],
            tokens[2],
            std::stod(tokens[3]),
            static_cast<unsigned short>(std::stoi(tokens[4])),
            tokens[5]
        );
    }

    



}