#include "Logger.h"

namespace seneca {

    //////////////////////////////////////
    // Copy Ops are disabled
    //////////////////////////////////////

   
  //Move constructor
  Logger::Logger(Logger&& src) noexcept {
    *this = std::move(src);
  }

  //Move Assignment Operator
  Logger& Logger::operator=(Logger&& src) noexcept {
    //check for self assignemnt
    if (this != &src) {
      //clean up resources
      delete[] m_events;

      //move -> take ownership of resources
      m_events = src.m_events;
      m_cnt = src.m_cnt;

      //reset the source object to a safe, empty state
      src.m_events = nullptr;
      src.m_cnt = 0;
    }
    return *this;
  }

   
  
   //Destructor
   Logger::~Logger()
   {
     delete[] m_events;
   }
   
    /**********************************
    * void addEvents()  
    * add to array a copy of event 
    * received a parameter
    ***********************************/
    void addEvent(const Event& event) {
        // 1. Allocate a brand new array
        //that is 1 element larger
        Event* temp = new Event[m_cnt + 1];

        //2. Copy existing elements over
        for (size_t i = 0; i < m_cnt; ++i) {
            temp[i] = m_events[i];
        }

        //3. Place the new event at the end of the new array
        temp[m_cnt] = event;

        //4. Deallocate old array and switch pointers
        delete[] m_events;
        m_events = temp;
        m_cnt++;
    }

    /****************************************
    * Friend Helper operator<<
    * -> inserts into the parameter events stored in Logger
    * -> received as second parameter
    * format:
    *     EVENT<endl>
    *     EVENT<endl>
    *
    *****************************************/
    std::ostream& operator<<(std::ostream& os, const Looger& log) {
        for (size_t i = 0; i < log.m_cnt; ++i) {
            os << log.m_events[i] << "\n";
        }
        return os;
    }

}