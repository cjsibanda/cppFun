#include <iomanip>
#include <iostream>
#include <string>

#include "Flags.h"
#include "File.h"

/**********************************************************
* File defines a class that holds information about a
* single file. A file is considered a resource of a filesystem
* File implements the Resource interface
***********************************************************/

namespace seneca {
    //custom constructor that receives two strings as parameters
    File::File(const std::string& name, const std::string& contents) : m_contents(contents) {
        m_name = name;
    }

    // sets tha parent path to the parameter
    void File::update_parent_path(const std::string& parent_path) {
        m_parent_path = parent_path;
    }

    // a query that returns Flags::File
    NodeType File::type() const {
        return NodeType::FILE;
    }

    // a query that returns the full absolute path of file
    // concatenates the absolute path location and the file name
    std::string File::path() const {
        return m_parent_path + m_name;
    }

    // a query that returns the name of the file
    std::string File::name() const {
        return m_name;
    }

    // a query that returns -1
    int File::count() const {
        return -1;
    }

    // a query that returns the size of the file in bytes
    // For simplicity, this is the number of characters in m_contents
    //in m_contents attribute
    size_t File::size() const {
        return m_contents.length();
    }
} 