#include <fstream> //check this??
#include <utility>
#include "Logger.h"

namespace seneca {
   Logger::Logger() {
    //
   }

   Logger::Logger(const Logger& src)
   {
      *this = src;
   }

   /////////////////////////////////////////
   //copy assignment op
   /////////////////////////////////////////
   Logger& Logger::operator=(const Logger& src)
   {
    //1. check for assignment
    if (this != &src)
    {
        //.2 clean up
        m_cnt = src.m_cnt;
        //delete[] m_something;
        //m_something = nullptr;
        //delete[] m_somethingElse;
        //m_somethingElse = nullptr;
        if (m_cnt != 0)
        {
            //m_something = new std::string[m_cnt];
            //m_somethingElse = new std::string[m_cnt];
            for (auto i = 0u; i < m_cnt; ++i)
            {
                //m_something[i] = src.m_something[i];
                //m_somethingElse[i] = src.m_proteinSequences[i];
            }
        }

    }
    return *this;

   }

   Logger::Logger(Logger&& src) noexcept
   {
    *this = std::move(src);
   }

   Logger& Logger::operator=(Logger&& src) noexcept
   {
      if (this != &src)
      {
        m_cnt = src.m_cnt;

        //delete[] m_something;
        //delete[] m_somethingElse;
        //m_something = src.m_something;
        //m_somethingElse = src.m_somethingElse;
        src.m_cnt = 0;
        //src.m_something = nullptr;
        //src.m_somethingElse = nullptr;
      }
      return *this;
   }

   //Destructor
   Logger::~Logger()
   {
    //delete[] m_something;
    //delete[] m_somethingElse;
   }
   


}