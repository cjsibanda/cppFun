#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <iostream>
#include <vector> //??
#include <string> //??

//define global variable g_settings 

/*********************************************************
* Contains the functionality regaerding the configuration
* of the application. 
*********************************************************/
namespace seneca 
{
  struct Settings 
  {
      int m_maxSummaryWidth{80};
      bool m_tableView{false};
      
  };

  extern Settings g_settings;
}
#endif