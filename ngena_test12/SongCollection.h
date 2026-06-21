#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H
#include <vector>
#include <string>
#include <list>

namespace seneca
{
    /*********************************************
    * The defines a simple struture called song
    * capable of storing the following information
    * about the song: artist, title, album, pricce
    * ... release year & length of year
    **********************************************/
    struct Song
    {
        std::string m_artist{};
        std::string m_title{};
        std::string m_album{};
        double m_price{};
        int m_releaseYear{};
        size_t m_songLength{}; //seocnds
    };


    
    /**************************************************
    * Song Manages a collection of objects of type song
    * Should us an STL container
    **************************************************/
    class SongCollection
    {
        //use vector
        std::vector<seneca::Song> m_songs;
        
        //trim??? maybe?
    public:
        //---------------------------------------------------
        // custom constructor that receives name as parameter
        // loads into the attributes at songs in the file
        // each line contains information aboutsong in the format:
        // TITLE ARTIST ALBUM YEAR LENGTH PRICE
        //---------------------------------------------------
        SongCollection(std::string name);
        //------------------------------------------
        //print content of collection into parameter
        //use insertion operator
        // at the end of collection list, display playtime
        // DO'NT USE MANUAL LOOPS
        //-------------------------------------------
        void SongCollection::display(std::ostream& out) const;
        //receive name parameter & sort in asc order
        void sort();
        //remove token from the album field of songs
        void cleanAlbum();
        //receives name of artist and returns true
        //if collection contains any song by the artist
        bool inCollection() const;
        //returns list of songs of that artist
        std::list<Song> getSongForArtist() const;

        /*****************************************
        * Free Helper
        * Inserts one sonf into the first parameter
        * uses the following format:
        * | TITLE(20) | ARTIST(15) | ALBUM(20) | YEAR(6) | LENGTH | PRICE |
        ******************************************/
        std::list<Song> getSongsForArtist() const;
    };
}