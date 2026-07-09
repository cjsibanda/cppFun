#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <numeric>



namespace seneca 
{
    class TvShow; //<-- forwared declaration so compiler knwows it exist
    //inside or outside class?
        struct TvEpisode
        {
            const TvShow* m_show{};
            unsigned short m_numberOverall{};
            unsigned short m_season{};
            unsigned short m_numberInSeason{};
            std::string m_airDate{};
            unsigned int m_length{};
            std::string m_title{};
            std::string m_summary{};
        };



    class TvShow : public MediaItem
    {
        /*****************************************************
        *  TvShow class stores the information for a TV show
        * m_id, title (inherited), release year (inherited)
        * the summary (inherited), m_epsiode
        ******************************************************/
        std::string m_id{};
        std::list<TvEpisode> m_episodes{};

        TvShow(
            const std::string& id,
            const std::string& title,
            unsigned short year,
            const std::string& summary
        );
        
        //add necessary constructors
        //constructors are private
    public:
        /********************************************************
        * override this function to print info about single book
        *********************************************************/
        void display(std::ostream& out) const override;

        /*****************************************************************
        * class function that receives as a parameter the representation
        * of the TV Show as a string a builds a dynamically allocated object
        * of type of TVShow using information from the string and returns it to
        * the client. The parameter contains a single line of text extracted
        * from the file tvShows.csv.
        ******************************************************************/
        static TvShow* createItem(const std::string& strShow);

        /*************************************************************
        * a class function that function builds an episode with the
        * information from the string, searches in the collection for 
        * a TV show with the specified id, and adds it to the list of
        * episodes of the found show.
        ***************************************************************/
        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode)
        {
            if (strEpisode.empty() || strEpisode[0] == '#')
                throw "Not a valid episode.";

            std::string tokens[8];
            size_t start = 0;
            size_t end = 0;


            for (int i = 0; i < 7; i++)
            {
                end = strEpisode.find(',', start);
                tokens[i] =
                    strEpisode.substr(
                        start,
                        end - start
                    );
                trim(tokens[i]);
                start = end + 1;
            }


            tokens[7] =
                strEpisode.substr(start);

            trim(tokens[7]);


            for (unsigned int i = 0;
                 i < col.size();
                 ++i)
            {
                TvShow* show =
                    dynamic_cast<TvShow*>(col[i]);


                if (show &&
                    show->m_id == tokens[0])
                {

                    TvEpisode ep;
                    ep.m_show = show;
                    ep.m_numberOverall =
                        static_cast<unsigned short>(
                            std::stoi(tokens[1]));

                    ep.m_season =
                        tokens[2].empty()
                        ?
                        1
                        :
                        static_cast<unsigned short>(
                            std::stoi(tokens[2]));

                    ep.m_numberInSeason =
                        static_cast<unsigned short>(
                            std::stoi(tokens[3]));

                    ep.m_airDate = tokens[4];
                    ep.m_length =
                        static_cast<unsigned int>(
                            std::stoi(tokens[5]));

                    ep.m_title = tokens[6];
                    ep.m_summary = tokens[7];
                    show->m_episodes.push_back(ep);
                    return;
                }
            }


            throw std::string(
                "Show not found: "
                + tokens[0]);
        }


        // get the avg length in seconds of the episode
        //MUST accomplish this using STL Algorithms and NO manual loops
        // The lambda expression should not capture anything from the context by reference
        double getEpisodeAverageLength() const;

        //create a list with episode names that are at least 1 hour long
        //MUST accomplish this using STL Algorithms and NO manual loops
        // The lambda expression should not capture anything from the context by reference
        std::list<std::string> getLongEpisodes() const; 

    };
}
#endif