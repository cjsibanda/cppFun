#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {
    /************************************************
    * class Guild manages dynamically allocated collection
    * of characters in the form of an array 
    * -> works with array of pointers to Character
    * stores address to array
    * -> Guild is in AGGREGATION relationship with Character
    *************************************************/
    class Guild {
        Character** m_members = nullptr; //stores addree of array
        size_t m_size = 0;
        std::string m_name; //string with name of guild
    public:
        Guild() = default; //default constructor
        Guild(const char* name); //creates guild with parameter name
        ~Guild();
        
        // Rule of 5
        Guild(const Guild& other);
        Guild& operator=(const Guild& other);
        Guild(Guild&& other) noexcept;
        Guild& operator=(Guild&& other) noexcept;

        /*******************************************
        * adds the character received as a parameter
        * to guild ONLY if it's not already in guild
        * Resize array if necessary
        *******************************************/
        void addMember(Character* c);

        //searches guild for parameter name
        //removes it
        void removeMember(const std::string& name);

        //returns character at the index specified by parameter
        Character* operator[](size_t idx) const;

        /********************************************
        * Prints tp the screen the current object in format
        *  [Guild] GUILD_NAME<endl>
        *    1: FIRST_CHARACTER<endl>
        *    2: SECOND_CHARACTER<endl>
        *    3: THIRD_CHARACTER<endl>
        *    ...
        * 
        * uses operator<< defined for the class Charater to
        * print a single character.
        * 
        *********************************************/
        void showMembers() const;
    };
}
#endif