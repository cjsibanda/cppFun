//IMPORTANT!! ... Review Input & Output Ops
//Rule of 5
//Copy and Move Semantics
// used m_UniqueIDs
// used m_aminoSequences
#include <fstream>
#include <utility>
#include "ProteinDatabase.h"

namespace seneca
{
    
    ProteinDatabase::ProteinDatabase() : m_aminoSequences(nullptr), m_cnt(0) {}

    /***************************************************************
    *-> 1-argument constructor that receives as parameter string  
    * containing a file from which member function populates curr obj
    * -> reads file to count the number of protein sequnces in file
    * -> allocates memory for that number of protein sequnces
    * -> re-reads the file and loads the protein sequences
    ****************************************************************/
    ProteinDatabase::ProteinDatabase(const std::string& filename)
    {
        std::ifstream f(filename.c_str());

        m_cnt = 0;
        m_aminoSequences = nullptr;
        if (!f)
            return;

        std::string line, uid, name;
        //count the number of protein sequences
        while (std::getline(f, line).good())
        {
            if (line[0] == '>') {
                //start of a new protein
                m_cnt++;
            }
        }

        f.clear();
        f.seekg(std::ios::beg);
        m_UniqueIDs = new std::string[m_cnt];
        m_aminoSequences = new std::string[m_cnt];
        line.clear(); 
        int i = -1;
        while (std::getline(f, line).good())
        {
            if (line[0] == '>') {
                //start of a new protein
                ++i;

                name = line.substr(1);

                //extract the Unique ID
                //Unique ID starts at index 4
                m_UniqueIDs[i] = line.substr(4u, line.find_first_of('|', 4u) - 4u);
            }
            else {
                m_aminoSequences[i] += line;
            }
        }
    }

    /*************************************
    * RULE OF 5
    * Copy Assignment Op
    * Copy Constructor??
    * Descructor
    * Implementing Move Semantics?
    ***************************************/

    ProteinDatabase::ProteinDatabase(const ProteinDatabase& src)
    {
        *this = src;
    }

    
    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src)
    {
        if (this != &src)
        {
            m_cnt = src.m_cnt;
            //does order matter???
            delete[] m_UniqueIDs;
            m_UniqueIDs = nullptr;
            delete[] m_aminoSequences;
            m_aminoSequences = nullptr;

            if (m_cnt != 0)
            {
                m_UniqueIDs = new std::string[m_cnt];
                m_aminoSequences = new std::string[m_cnt];
                for (auto i = 0u; i < m_cnt; ++i)
                {
                    m_UniqueIDs[i] = src.m_UniqueIDs[i];
                    m_aminoSequences[i] = src.m_aminoSequences[i];
                }
            }
        }
        return *this;
    }

    ///////////////////////////////////////////////////
    // Move Constructor
    //////////////////////////////////////////////////
    ProteinDatabase::ProteinDatabase(ProteinDatabase&& src) noexcept
    {
        *this = std::move(src);
    }

    
    ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src) noexcept
    {
       if (this != &src)
       {
        m_cnt = src.m_cnt;

        // does order matter?????????????
        delete[] m_UniqueIDs;
        delete[] m_aminoSequences;
        m_UniqueIDs = src.m_UniqueIDs;
        m_aminoSequences = src.m_aminoSequences;
        src.m_cnt = 0;
        src.m_aminoSequences = nullptr;
        src.m_UniqueIDs = nullptr; 
       }
       return *this;
    }
  
    /////////////////////////////////
    //Destructor
    //////////////////////////////////
    ProteinDatabase::~ProteinDatabase()
    {
        delete[] m_UniqueIDs;
        delete[] m_aminoSequences;
    }


    //////////////////////////////////////////////////////////
    // -> a query that returns a copy of the protein sequence
    // ... at the idex received as the function parameter
    // -> If the index is valid - function should return empy string
    //////////////////////////////////////////////////////////
    std::string ProteinDatabase::operator[](size_t idx) const
    //--> always use const??? 
    {
        if (idx < m_cnt)
          return m_aminoSequences[idx];
        return "";
    }

    /////////////////////////////////////////////////////////
    // -> query that returns a copy of the protein Id at the
    // ... index received as the function parameter.
    // -> If the index is invalid, this function should
    // ... return "None"
    //////////////////////////////////////////////////////////
    std::string ProteinDatabase::getUID(size_t idx) const
    {
        if (idx < m_cnt)
          return m_UniqueIDs[idx];
        return "None";
    }
    
}


////////////////////////////////////////////////
// IMPORTANT: Review Input & Output Ops
////////////////////////////////////////////////