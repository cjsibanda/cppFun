#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

#include "SongCollection.h"

//void printbar(std::ostream& out);



namespace seneca {
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

       //this needs work??!!
       while (file)
       {
        Song song;
        std::string line;
        std::getline(file, line);
        if (file)
        {
            //------------------>
            //song.m_title;
            //song.m_artist;
            //song.m_album;
            //<--------------------
            
            song.m_songLength = 0;
            song.m_price = 0.0;
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
			std::sort(m_songs.begin(), m_songs.end(), [](const Song& a, const Song& b) { return a.m_title < b.m_title; });
		else if (field == "album")
			std::sort(m_songs.begin(), m_songs.end(), [](const Song& a, const Song& b) { return a.m_album < b.m_album; });
		else if (field == "length")
			std::sort(m_songs.begin(), m_songs.end(), [](const Song& a, const Song& b) { return a.m_songLength < b.m_songLength; });
   }

   /******************************************************
   * Receives the name of an artist as a parameter 
   * returns true if collection contains song by artist
   * NO MANUAL LOOPS
   *******************************************************/
   bool SongCollection::inCollection(const std::string& artist) const
   {
        auto res = std::find_if(m_songs.begin(), m_songs.end(), [&artist](const Song& aSong) {return aSong.m_artist == artist; });
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

  //try this...
  std::ostream& operator<<(
    std::ostream& out,
    const Song& song)
  {
    out << song.m_title;
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