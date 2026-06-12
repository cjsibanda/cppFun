#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include <vector>
#include <ostream>

#include "Resource.h"
#include "Directory.h"
#include "File.h"
#include "Flags.h"

namespace seneca {
    /***************************************************************
    * Filesystem defines a class that represents a simple UNIX-like 
    * filesystem. Lets you move through root directory which holds all
    * filesystems resources
    ****************************************************************/
    class Filesystem {
        Directory* m_root = nullptr; //a pointer to the fielsystem root directory 
        Directory* m_current = nullptr; //pointer to current working directory

       // std::string_trim(std::string); ???
    public:
       Filesystem(const char*, const std::string & = " "); //custom constructor
       Filesystem(const Filesystem&) = delete; //no copy ops
       Filesystem& operator=(const Filesystem&) = delete; //no copy ops
       Filesystem(Filesystem&&) noexcept; //move constructor
       Filesystem& operator=(Filesystem&&) noexcept; //move assignment ops
       ~Filesystem(); //destructor

       Filesystem& operator+=(Resource*); //adds resource to current directory
       Directory* change_directory(const std::string & = ""); //change current directory
       Directory* get_current_directory() const;
    };
}

#endif