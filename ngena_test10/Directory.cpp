#include <forward_list>
#include <iomanip>
#include <ostream>
#include <string>
#include <vector>
#include "Directory.h"
#include "File.h"

namespace seneca {
    //Desctructor
    Directory::~Directory()
    {
        while (!m_content.empty())
        {
            delete m_contents.back();
            m_contents.pop_back();
        }
    }

    /********************************************
    * Sets the parent path to the parameter.
    * set absolute path for each resource directory holds
    ********************************************/
    void Directory::update_parent_path(const std::string& parent_path) {
        m_parent_path = parent_path;

        for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
            (*it)->update_parent_path(this->path());
        } 
    }

    //query that returns Flags::DIR
    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    // query that returns absolute full path of directory
    //
    std::string Directory::path() const {
      return m_parent_path + name();  
    }

    //query that returns the name of directory
    std::string Directory::name() const {
        return m_name;
    }

    //query that returns number of resources 
    //directory holds
    int Directory::count() const {
        return m_contents.size();
    }

    //returns the size of the direcory in bytes
    size_t Directory::size() const {
        return m_contents.size();
    }



     size_t Directory::size() const {
        size_t s = 0u;

        for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
            s += (*it)->size();
        }

        return s;
    }

    Directory& Directory::operator+=(Resource* resource) {
        for (Resource* r : m_contents) {
            std::string r_name = r->name();

            if (r_name == resource->name()) {
                throw std::string("Resource already exists in directory!");
            }
        }

        m_contents.push_back(resource);
        resource->update_parent_path(path());

        return *this;
    }

    //remove deletes a resource from the directory 
    //
    void Directory::remove(const std::string& rname, const std::vector<OpFlags>& flags) {
   
      //???????
    }

    
    



}