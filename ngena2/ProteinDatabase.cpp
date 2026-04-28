//double check...
#include <fstream>
#include <utility>
#include "ProteinDatabase.h"

namespace sibanda {
    ProteinDatabase::ProteinDatabase(nullptr), m_cnt(0) {}

    ProteinDatabase::ProteinDatabase(const std::string& filename)
    {
       std::ifstream f(filename.c_str());

       m_cnt = 0;
       m_proteinSequences = nullptr;
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
    }

    f.clear();
    f.seekg(std::ios::beg);
    m_proteinUIDs = new std::string[m_cnt];
    m_proteinSequences = new std::string[m_cnt];
    line.clear();
    int i = -1;
    while (std::getline(f, line).good())
    {
        if (line[0] == '>') {
            //start of a new proteir
            ++i;

            name = line.substr(1);

            //extract the Unique ID
            m_proteinUIDs[i] = line.substr(4u, line.find_first_of('|', 4u) - 4u);
        }
        else
        {
            m_proteinSequences[i] += line;
        }
    }
}

ProteinDatabase::ProteinDatabase(const ProteinDatabses& src)
{
    *this = src;
}

ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src)
{
    if (this != &src)
    {
        m_cnt = src.m_cnt;

        delete[] m_proteinUIDs;
        m_proteinUIDs = nullptr;
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
    return *this;
}

ProteinDatabase::ProteinDatabase(ProteinDatabase&& src) noexcept
{
    *this = std::move(src);
}

ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src) noexcept
{
    if (this != &src)
    {
        m_cnt = src.m_cnt;

        delete[] m_proteinUIDs;
        delete[] m_proteinSequences;
        m_proteinUIDs = src.m_proteinUIDs;
        m_proteinSequences = src.m_proteinSequences;
        src.m_cnt = 0;
        src.m_proteinSequences = nullptr;
        src.m_proteinUIDs = nullptr;
    }
    return *this;
}

ProteinDatabase::~ProteinDatabase()
{
    delete[] m_proteinUIDs;
    delete[] m_proteinSequences;
}

std::string Proteindatabase::operator[](size_t idx) const
{
  if (idx < m_cnt)
      return m_proteinSequences[idx];
  return "";
}

std::string ProteinDatabse::getUID(size_t idx) const
 {
   if (idx < m_cnt)
     return m_proteinUIDs[idx];
return "None";
 }
}