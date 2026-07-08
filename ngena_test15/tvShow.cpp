#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

#include "tvShow.h"
#include "settings.h"


namespace seneca
{
    /*****************************************************
    * TvShow that stores information for a tv show
    * m_id, title, year of release, the summary, m_episods
    ******************************************************/
    TvShow::TvShow(
      const std::string& id;
      const std::string& title,
      unsigned short year,
      const std::string& summary
    )
      : MediaItem(title, summary, year),
      m_id(id)
     {
     } 

    /*****************************************************
    * override this function to print the information
    * about a single book 
    *****************************************************/
    void TvShow::display(std::ostream& out) const
    {
      if (g_settings.m_tableView)
      {
        out << "S | ";
        out << std::left << std::setfill('.');
        out << std::setw(50) << this->getTitle() << " | ";
        out << std::right << std::setfill(' ');
        out << std::setw(2) << this->m_episodes.size() << " | ";
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
        out << this->getTitle() << " [" << this->getYear() << "]\n";
        out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
        while (pos < this->getSummary().size())
        {
          out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
          pos += g_settings.m_maxSummaryWidth;
        }
        for (auto& item : m_episodes)
        {
          out << std::setfill('0') << std::right;
          out << "    " << 'S' << std::setw(2) << item.m_season
            << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
          if (item.m_title != "")
            out << item.m_title << '\n';
          else
            out << "Episode " << item.m_numberOverall << '\n';

          pos = 0;
          while (pos < item.m_summary.size())
          {
            out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
            pos += g_settings.m_maxSummaryWidth - 8;
          }
        }
        out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
          << std::setfill(' ') << '\n';
      }
    }

    /****************************************************
    * a class function that receives as parameter the 
    * representation of the TV Show as a string and
    * builds a dynamically allocated object of type TvShow
    * using the information from the string and returns it 
    * to the client. The parameter contains a single line of
    * text extracted from the file tvShows.csv
    * The format is the following:
    *    ID,TITLE,YEAR,SUMMARY
    * The function should remove all spaces from the beginning
    * and end of any token in the string
    *****************************************************/
    TvShow* TvShow::createItem(const std::string& strShow)
    {
        if (strShow.empty() || strShow[0] == '#')
           throw "Not a valid show.";

        std::string tokens[4];

        size_t start = 0;
        size_t end = 0;

        for (int i = 0; i < 3; i++)
        {
          end = strShow.find(',', start);

          token[i] = strShow.substr(start, end - start);

          trim(tokens[i]);
          start = end + 1;
        }

        tokens[3] = strShow.substr(start);

        trim(tokens[3]);

        return new TvShow(
          tokens[0],
          tokens[1],
          static_cast<unsigned short>(
              std::stoi(token[2])
          ),
          tokens[3]
        );


    }

    /*************************************************
    * a class function that function builds an episode
    *  with the information from the string, searches in
    *  the collection for a TV show with the specified
    *  id, and adds it to the list of episodes of the 
    * found show. The string parameter contains a single
    *  line of text extracted from the file episodes.csv 
    * Output should have this format:
    * ID,EPISODE_NUMBER,SEASON_NUMBER,EPISODE_IN_SEASON,AIR_DATE,LENGTH,TITLE,SUMMARY
    ***************************************************/
    template<typename Collection_t>
    void addEpisode(Collection_t& col, const std::string& strEpisode)
    {
      ////

    }

    //get avgerage length in seconds of an episode
    // Must use STL algorithms
    //no manual loops
    //lambda should not capture anything from the contest by reference
    double TvShow::getEpsiodeAverageLength() const
    {
      if (m_episode.empty())
         return 0;
      
      unsigned int total = std::accumulate(
        m_episodes.begin(),
        m_episode.end(),
        0u,
        [](unsigned int sum, const TvEpisode& ep)
        {
          return sum + ep.m_length;
        }
      );

      return static_cast<double>(total)/m_episodes.size();

    }

    /*******************************************************
    * get list with episode names that are at least 1 our long
    ********************************************************/
    std::list<std::string> TvShow::getLongEpisodes() const



}
