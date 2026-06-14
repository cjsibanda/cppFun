#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Directory.h"
#include "File.h"

namespace seneca {

    // Constructor
    Directory::Directory(const std::string& name) {
        m_name = name;
    }

    // Destructor
    Directory::~Directory() {
        for (auto& r : m_contents) {
            delete r;
        }
        m_contents.clear();
    }

    // Update parent path recursively
    void Directory::update_parent_path(const std::string& parent_path) {
        m_parent_path = parent_path;

        for (auto& r : m_contents) {
            r->update_parent_path(this->path());
        }
    }

    // Type
    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    // Path
    std::string Directory::path() const {
        return m_parent_path + m_name;
    }

    // Name
    std::string Directory::name() const {
        return m_name;
    }

    // Count
    int Directory::count() const {
        return static_cast<int>(m_contents.size());
    }

    // Size (recursive)
    size_t Directory::size() const {
        size_t total = 0;
        for (auto& r : m_contents) {
            total += r->size();
        }
        return total;
    }

    // Add resource
    Directory& Directory::operator+=(Resource* resource) {

        for (auto r : m_contents) {
            if (r->name() == resource->name()) {
                throw std::string("Resource already exists in directory!");
            }
        }

        m_contents.push_back(resource);
        resource->update_parent_path(this->path());

        return *this;
    }

    // FIND (recursive optional)
    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {

        for (auto r : m_contents) {
            if (r->name() == name) {
                return r;
            }
        }

        bool recursive = false;
        for (auto f : flags) {
            if (f == OpFlags::RECURSIVE)
                recursive = true;
        }

        if (recursive) {
            for (auto r : m_contents) {
                if (r->type() == NodeType::DIR) {
                    Resource* found = dynamic_cast<Directory*>(r)->find(name, flags);
                    if (found) return found;
                }
            }
        }

        return nullptr;
    }

    // REMOVE
    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {

        for (auto it = m_contents.begin(); it != m_contents.end(); ++it) {
            if ((*it)->name() == name) {

                if ((*it)->type() == NodeType::DIR) {
                    bool recursive = false;
                    for (auto f : flags)
                        if (f == OpFlags::RECURSIVE)
                            recursive = true;

                    if (!recursive) {
                        throw std::invalid_argument(
                            name + " is a directory. Pass the recursive flag to delete directories."
                        );
                    }
                }

                delete *it;
                m_contents.erase(it);
                return;
            }
        }

        throw std::string(name + " does not exist in " + m_name);
    }

    // DISPLAY
    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {

        bool longFormat = false;
        for (auto f : flags)
            if (f == FormatFlags::LONG)
                longFormat = true;

        os << "Total size: " << size() << " bytes\n";

        for (auto r : m_contents) {

            if (r->type() == NodeType::DIR) {
                os << "D | " << std::left << std::setw(15) << r->name();

                if (longFormat) {
                    os << " | " << std::setw(2) << r->count()
                       << " | " << std::setw(10) << r->size() << " bytes |";
                }

                os << "\n";
            }
            else {
                os << "F | " << std::left << std::setw(15) << r->name();

                if (longFormat) {
                    os << " |    | " << std::setw(10) << r->size() << " bytes |";
                }

                os << "\n";
            }
        }
    }

}