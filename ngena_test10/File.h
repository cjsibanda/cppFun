#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include <string>
#include <ostream>

#include "Resource.h"

namespace seneca {
    /*************************************************
    * File holds information about a single file.
    * A file is considered a resource of a filesystem
    * File Implements the resource interface
    **************************************************/
    class File : public Resource {
        std::string m_contents; //stores the contents of a file
    public:
        //custom constructor
        File(const std::string&, const std::string & = "");
        //sets parent path to parameter
        void update_parent_path(const std::string&);
        //Query that returns Flags::File
        NodeType type() const;
        std::string path() const; //returns full absolute path
        std::string name() const;
        int count() const; // a query that returns -1?
        size_t size() const; //returns the size of the file in bytes
    };
}
#endif