//change file name (Proteint)
//Proofread .. continue


#include <fstream>
#include <utility>
#include "ProteintDatabase.h"

namespace sibanda
{
    ProteinDatabase::ProteinDatabase() : m_proteinSequences(nullptr), m_cnt(0) {}

    ProteinDatabase::ProteinDatabase(const std::string& filename)
    {
        std::ifstream f(filename.c_str());

        m_cnt = 0;
        m_proteinSequences = nullptr;
        if (!f) 
           return;
        
        std::string line, uid, name;
        //counting the number of protein sequences
        while (std::getline(f, line).good())
        {
            if (line[0] == '>') {
                m_cnt++;
            }
        }

        f.clear();
        f.seek(std::ios::beg);
        m_proteinUIDs = new std::string[m_cnt];
        m_proteinSequences = new std::string[m_cnt];
        line.clear();
        int i = -1;
        while (std::getline(f, line).good())
        {
            if (line[0] == '>') {
                ++1;

                name = line.substr(1);

                //extracting unique id
                m_proteinUIDs[i] = line.substr(4u, line.find_first_of('|', 4u) - 4u);

            }
            else 
            {
                m_proteinSequences[i] += line;
            }
        }
    }

    ProteinDatabase::ProteinDatabase(const ProteinDatabase& src) {
        *this = src;
    }

    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src)
    {
        m_cnt = src.m_cnt;

        delete[] m_proteinUIDs;
        m_proteinSequences = nullptr;
        delete[] m_proteinSequences;
        m_proteinSequences = nullptr;

        if (m_cnt != 0)
        {
            m_proteinUIDs = new std::string[m_cnt];
            m_proteinSequences = new std::string[m_cnt];
            for (auto i = 0u; i < m_cnt; ++i)
            {
                m_proteinUIDs[i] = src.m_proteinUIDs[i];
                m_proteinSequences[i] = src.m_proteinSequences[i];
            }
        }
    }
    //return *this;
}

