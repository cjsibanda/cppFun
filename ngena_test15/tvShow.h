#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <vector>
#include <string>
#include <list>
#include <ostream>

namespace seneca 
{


    class TvShow
    {
        /*****************************************************
        *  TvShow class stores the information for a TV show
        * m_id, title (inherited), release year (inherited)
        * the summary (inherited), m_epsiode
        ******************************************************/

        //inside or outside class?
        struct TvEpisode
        {
            const TvShow* m_show{};
            unsigned short m_numberOverrall{};
            unsigned short m_season{};
            unsigned short m_numberInSeason{};
            std::string m_airDate{};
            unsigned int m_length{};
            std::string m_title{};
            std::string m_summary{};
        };

        //add necessary constructors
        //constructors are private
    public:
        /********************************************************
        * override this function to print info about single book
        *********************************************************/
        void display(std::ostream& out) const override

        /*****************************************************************
        * class function that receives as a parameter the representation
        * of the TV Show as a string a builds a dynamically allocated object
        * of type of TVShow using information from the string and returns it to
        * the client. The parameter contains a single line of text extracted
        * from the file tvShows.csv.
        ******************************************************************/
        TvShow* createItem(const std::string& strShow);

        /*************************************************************
        * a class function that function builds an episode with the
        * information from the string, searches in the collection for 
        * a TV show with the specified id, and adds it to the list of
        * episodes of the found show.
        ***************************************************************/
        template<typename Collection_t>
        void addEpisode(Collection_t& col, const std::string& strEpisode)

        // get the avg length in seconds of the episode
        //MUST accomplish this using STL Algorithms and NO manual loops
        // The lambda expression should not capture anything from the context by reference
        double getEpisodeAverageLength() const:

        //create a list with episode names that are at least 1 hour long
        //MUST accomplish this using STL Algorithms and NO manual loops
        // The lambda expression should not capture anything from the context by reference
        std::list<std::string> getLongEpisodes() const 

    };
}
#endif