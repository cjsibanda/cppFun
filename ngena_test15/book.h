#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <vector> //??
#include <string>

namespace seneca
{
    class Book 
    {
        std::string m_author{}
        //title inherited
        std::string m_country{};
        //year of publication inherited
        double m_price //price of the book
        //the summary (inherited): a short description of the book
        Book(),
        //other constructors needed?
    public:
        /*************************************
        *  Override this function
        * to print info about single book
        *************************************/
        void display(std::ostream& out) const;
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
       Book* createItem(const std::string& strBook)

    }

}
#endif