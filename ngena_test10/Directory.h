#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include <vector>
#include <forward_list>

#include "Flags.h"
#include "Resource.h"

namespace seneca {
    /*****************************************************
    * This class represents a directory in the filesystem
    * a directory is considered a resouce of a filesystem.
    * A directory can hold many other directories and files
    ******************************************************/
    class Directory : public Resource {
        //holds pointers to resource objects
        //each element can be either a Directory or File
        std::vector<Resource*> m_contents;

       // template???
       // template<typename T>
       //bool has_flag_set(std::vector<T>, T) const;
    public:
        Directory(const std::string&); //custome constuctor
        ~Directory(); //destructor
        Directory& operator+=(Resource*); //adds resource to the directory

        /**********************************************
        * finds and returns the address of a resource
        * in directory whose name mateches the given string
        ***********************************************/
        Resource* find(const std::string&, const std::vector<OpFlags>& = {});

        void update_parent_path(const std::string&) override;
        NodeType type() const override; //a query that will return Flags::DIR
        std::string path() const override;
        std::string name() const override;
        size_t size() const override;
        int count() const override;

        void remove(const std::string&, const std::vector<OpFlags>& = {});
        void display(std::ostream&, const std::vector<FormatFlags>& = {}) const;
    }; 
}
#endif