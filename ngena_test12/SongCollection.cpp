#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

#include "SongCollection.h"

//--------------------------------------------->
//Need Trim helper?
// Any blank space at the beginning/end of token
//...should be removed
//<-----------------------------------------------
static std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');

    if (first == std::string::npos)
       return "";

    return str.substr(first, last - first + 1);
}



namespace seneca {
    //<-------------------------------------------
    /************************************************************************************
    * Custom Constructor - receives name of the file as parameter
    * The function should load into the attributes all the songs of the file
    * Each line from the file contains info about a single song in the following format:
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

       //????
       std::string line;
       while (std::getline(file, line))
       {
        Song song;

        song.m_title = trim(line.substr(0,25));
        song.m_artist = trim(line.substr(25,25));
        song.m_album = trim(line.substr(50, 25));

        std::string year = trim(line.substr(75, 5));
        std::string length = trim(line.substr(80, 5));
        std::string price = trim(line.substr(85));

        song.m_releaseYear = year.empty() ? 0 : std::stoi(year);
        song.m_songLength = std::stoul(length);
        song.m_price = std::stod(price);

        m_songs.push_back(song);

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

      //might need this
      //printbar(out);

      out << "| "
          << std::setw(84)
          << ("Total Listening Time: "
             + std::to_string(hours) + ":"
             + std::to_string(minutes) + ":"
             + std::to_string(seconds))
          << " |\n";
   }

   /***************************************************************
   * Receives name parameter of field used to sort collection
   * Sort in Ascending order
   * Parameter can have one of the values titel, album, or length
   * NO MANUAL LOOPS
   ****************************************************************/
   void SongCollection::sort(const std::string& field)
   {
      if (field == "title")
			std::sort(m_songs.begin(),
                      m_songs.end(),
                      [](const Song& a,
                      const Song& b)
                      { return a.m_title < b.m_title; });
		else if (field == "album")
			std::sort(m_songs.begin(),
                      m_songs.end(),
                      [](const Song& a,
                      const Song& b) 
                      { return a.m_album < b.m_album; });
		else if (field == "length")
			std::sort(m_songs.begin(),
                      m_songs.end(), 
                      [](const Song& a, 
                      const Song& b) 
                      { return a.m_songLength < b.m_songLength; });
   }

   /******************************************************
   * Receives the name of an artist as a parameter 
   * returns true if collection contains song by artist
   * NO MANUAL LOOPS
   *******************************************************/
   bool SongCollection::inCollection(const std::string& artist) const
   {
        auto res = std::find_if(
            m_songs.begin(),
            m_songs.end(), 
            [&artist](const Song& aSong) 
            {return aSong.m_artist == artist; });
        return res != m_songs.end();
   }

   /********************************************************
   * Removes the token [None] from the album field of songs
   * that do not have a valid album
   *********************************************************/
  void SongCollection::cleanAlbum() 
  {
    std::for_each(
        m_songs.begin(),
        m_songs.end(),
        [](Song& song) 
        {
            if (song.m_album == "[None]")
            song.m_album = "";
        });
    
  }

  
  std::ostream& operator<<(
    std::ostream& out,
    const Song& song)
  { 
    
    int min = song.m_songLength / 60;
    int sec = song.m_songLength % 60;

    out << "| "
        << std::left << std::setw(20) << song.m_title << " | "
        << std::setw(15) << song.m_artist << " | "
        << std::setw(20) << song.m_album << " | "
        << std::right << std::setw(6);

    if (song.m_releaseYear != 0)
        out << song.m_releaseYear;
    else
        out << "";

    out << " | "
        << min << ":"
        << std::setw(2) << std::setfill('0') << sec
        << std::setfill(' ') << " | "
        << std::fixed << std::setprecision(2)
        << song.m_price << " |";

    return out;

  }
    

  

  /*****************************************************************
  * receives the name of an artist as a parameter
  * returns the list of songs that artists available in collection
  *****************************************************************/
  std::list<Song> 
  SongCollection::getSongsForArtist(
    const std::string& artist
  ) const
  { 
      std::list<Song> songs;

      std::copy_if(
          m_songs.begin(), 
          m_songs.end(), 
          std::back_inserter(songs), 
          [&artist](const Song& aSong)
      {
         return aSong.m_artist == artist;
      });
      return songs;
  }

}
