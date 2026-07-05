#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <vector>
#include <string>
#include <list>
#include <ostream>

namespace seneca 
{
    /***************************************************
    * Class Movie stores the the following information
    * for a single movie.
    * For each attribute, choose a type that is appropriate
    * must be able to justify decisions...
    * title (inherited), the year of release(inherited), 
    * the summary (inherited)
    ****************************************************/
    class Movie 
    {
       ///title (inherited)
       //the year of release (inherited)
       // the summary (inherited)

       //add constructors necessary for design
       //constructors should be private
    public:
        /*******************************************************
        * override this function to print info about single book
        ********************************************************/     
        void display(std::ostream& out) const override;

        /****************************************
        * a class function that receives as a parameter
        * the representation of the movie as a string and
        * builds a dynamically allocated object of type Movie
        * using information from the string and returns it to
        * the client.
        ******************************************/
        Movie* createItem(std::string& strMovie)
     
    }


}