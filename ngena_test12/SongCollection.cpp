#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <string>
#include "SongCollection.h"

void printbar(std::ostream& out);



namespace seneca {
    /************************************************************************************
    * Custom Constructor - receives name of the file as parameter
    * The function should load into the attributes all the songs of the file
    * Eachh line from the file contains info about a single song in the following format:
    *      TITLE ARTIST ALBUM YEAR LENGTH PRICE   
    * Fields are NOT seperated by delimiters
    * Each field has fixed size exactly 25 characters
    * Length of a song in input is stored in seconds
    * 
    ************************************************************************************/
   SongCollection::SongCollection(const std::string& filename)
   {
       std::ifstream file(filename);
       if (!file)
             throw "Invalid filename!";

       //this needs work??!!
       while (file)
       {
        Song song;
        std::getline(file);
        if (file)
        {
            this->song.m_title;
            this->song.m_artist;
            this->song.m_album;
            try
            {
                song.m_releaseYear = this->m_releaseYear;
            }
            catch(...)
            {
                song.m_releaseYear = 0; //???
            }
            song.m_songLength = this->m_songLength;
            song.m_price = this->m_songPrice;
            this->m_songs.push_back(song);
        }
       }
       file.close();

   }

   /******************************************************
   * print the content of collection into parameter
   * Use insertion operator
   * display total playtime at the end of collection list
   * total playtime = sum of the length attribute of all songs
   * 
   ********************************************************/
   void SongCollection::display(std::ostream& out) const
   {
      std::for_each(m_songs.begin(), m_songs.end(),
         [&out](const Song& song)
         {
            out << song << '\n';
         });
       
       size_t totalSeconds = std::accumulate(
        m_songs.begin(),
        m_songs.end(),
        size_t(0),
        [](size_t total, const Song& song)
        {
            return total + song.m_songLength;
        });

      size_t hours = totalSeconds / 3600;
      size_t minutes = (totalSeconds % 3600 ) / 60;
      size_t seconds = totalSeconds % 60;

      printbar(out);

      out << "| "
          << std::setw(84)
          << ("Total Listening Time: "
             + std::to_string(hours) + ":"
             + std::to_string(minutes) + ":"
             + std::to_string(seconds))
          << " |\n";
   }




}