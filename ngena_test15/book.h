#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <vector> //??
#include <string>
#include "mediaItem.h"

namespace seneca
{
    /**************************************************
    * Book class is derived from MediaItem that can store
    * information (for each attribute, chose any type
    * that you think is appropriate) - be able to justiy
    * decisions.
    ****************************************************/
    class Book : public MediaItem
    {
        std::string m_author{};
        std::string m_country{};
        double m_price{};

        Book(
            const std::string& author,
            const std::string& title,
            const std::string& country,
            double price,
            unsigned short year,
            const std::string& summary
        );

    public:
        /*************************************
        *  Override this function
        * to print info about single book
        *************************************/
        void display(std::ostream& out) const override;
        /***********************************************
        *  a class function that receives as a parameter
        * the representation of the book as a string and 
        * builds a dynamically allocated object of type Book
        * using the information from the string
        * ... returns it to the client.
        * Paramter contains a single line of text extracted 
        * from books.csv. line should have the following format
        * *** AUTHOR,TITLE,COUNTRY,PRICE,YEAR,SUMMARY ***
        ************************************************/
       static Book* createItem(const std::string& strBook)

    }

}
#endif