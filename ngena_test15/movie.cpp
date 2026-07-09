#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

#include "movie.h"
#include "settings.h"
#include "mediaItem.h"

namespace seneca 
{

   /*****************************************************
   * Class Movie stores info about single movie
   * title (inherited), realease Year (inherited), summary (inherited)
   *****************************************************/
    Movie::Movie(
        const std::string& title,
        unsigned short year,
        const std::string& summary
    )
        :
        MediaItem(title, summary, year)
    {
    }


    //override this function
    //to print the info about a single book
    void Movie::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
      {
        out << "M | ";
        out << std::left << std::setfill('.');
        out << std::setw(50) << this->getTitle() << " | ";
        out << std::right << std::setfill(' ');
        out << std::setw(9) << this->getYear() << " | ";
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
        out << this->getTitle() << " [" << this->getYear() << "]\n";
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



    //a class function that receives as a parameter the
    // representation of the movie as a string and builds
    // a dynamically allocated object if type movie
    // format of the line is
    // TITLE,YEAR,SUMMARY
    // function removes all spaces from the beginning and end of
    //any token string
    Movie* Movie::createItem(const std::string& strMovie)
    {
        if (strMovie.empty() || strMovie[0] == '#')
            throw "Not a valid movie.";


        std::string title;
        std::string year;
        std::string summary;


        size_t first = strMovie.find(',');
        size_t second = strMovie.find(',', first + 1);


        title = strMovie.substr(0, first);

        year = strMovie.substr(
            first + 1,
            second - first - 1
        );

        summary = strMovie.substr(second + 1);


        trim(title);
        trim(year);
        trim(summary);


        return new Movie(
            title,
            static_cast<unsigned short>(std::stoi(year)),
            summary
        );
    }

}