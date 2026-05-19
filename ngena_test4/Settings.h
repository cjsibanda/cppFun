#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <iostream>

namespace seneca {
    /******************************** 
    * -> contains functionality regarding configuration
    * of the application
    ********************************/
    // global varibale g_settings
    class Settings {
        bool m_show;
        bool m_verbose;
        std::string* m_time_units;
    }
    

}
#endif