//Copy & Move semantics
// ProteinDatabase.h
#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <string>

namespace seneca 
{
    /*****************************************
    * -> ProteinDatabase manages two paralel dynamically allocated arrays
    * ... of type std::string 
    * -> one array will store the Unique IDs of the proteins
    * -> second array will store sequence of amino acids making protein
    * -> class keeps track of the number of proteins currently stored
    ******************************************/
    class ProteinDatabase
    {
        std::string* m_UniqueIDs{ nullptr };
        std::string* m_aminoSequences{ nullptr };
        size_t m_cnt{ 0 };
    public:
       /////////////////////////////////////////
       // -> no arg, 1-arg constructor
       // -> Rule of 5
       /////////////////////////////////////////
        ProteinDatabase();
        ProteinDatabase(const std::string&);
        ProteinDatabase(const ProteinDatabase&);
        ProteinDatabase(ProteinDatabase&&) noexcept;
        ProteinDatabase& operator=(const ProteinDatabase&);
        ProteinDatabase& operator=(ProteinDatabase&&) noexcept;

        ~ProteinDatabase();

        /***************************************************
        * -> size_t size(): query returns number of sequences
        * in the current object
        * -> std::string operator[](size_t): query that returns
        * copy of the protein sequence at index received as parameter
        * -> std::string getUID(size_t): a query that returns copy of
        * protein ID at index received as function parameter.  
        *****************************************************/
        size_t size() const { return m_cnt; }
        std::string operator[](size_t idx) const;
        std::string getUID(size_t idx) const;

    };
}
#endif