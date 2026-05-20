#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <iostream>
#include <string>

namespace seneca {
    /******************************** 
    * -> contains functionality regarding configuration
    * of the application
    ********************************/
    // global varibale g_settings
    extern Settings g_settings; ////put it here???
     
    // no class, just struct??
    struct Settings {
        bool m_show{ false };
        bool m_verbose{ false };
        std::string m_time_units{ "nanoseconds" };
    }


    

}
#endif