#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "Filesystem.h"
#include "Directory.h"
#include "File.h"

namespace seneca {

    // helper trim
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

    // constructor
    Filesystem::Filesystem(const char* filename, const std::string& root_name) {

        std::ifstream file(filename);
        if (!file) {
            throw std::invalid_argument("Invalid file");
        }

        m_root = new Directory(root_name);
        m_current = m_root;

        std::string line;

        while (std::getline(file, line)) {

            if (line.empty()) continue;

            size_t sep = line.find('|');

            std::string path;
            std::string content;

            if (sep == std::string::npos) {
                path = trim(line);
            }
            else {
                path = trim(line.substr(0, sep));
                content = trim(line.substr(sep + 1));
            }

            std::stringstream ss(path);
            std::string token;
            Directory* current = m_root;

            std::vector<std::string> parts;

            while (std::getline(ss, token, '/')) {
                if (!token.empty())
                    parts.push_back(token);
            }

            for (size_t i = 0; i < parts.size(); i++) {

                bool isLast = (i == parts.size() - 1);
                std::string name = parts[i];

                if (isLast && !content.empty()) {
                    current->operator+=(new File(name, content));
                }
                else {
                    Resource* found = current->find(name);

                    Directory* next = nullptr;

                    if (found) {
                        next = dynamic_cast<Directory*>(found);
                    }
                    else {
                        next = new Directory(name + "/");
                        *current += next;
                    }

                    current = next;
                }
            }
        }
    }

    // destructor
    Filesystem::~Filesystem() {
        delete m_root;
    }

    // move constructor
    Filesystem::Filesystem(Filesystem&& src) noexcept {
        *this = std::move(src);
    }

    // move assignment
    Filesystem& Filesystem::operator=(Filesystem&& src) noexcept {

        if (this != &src) {
            delete m_root;

            m_root = src.m_root;
            m_current = src.m_current;

            src.m_root = nullptr;
            src.m_current = nullptr;
        }

        return *this;
    }

    // add resource to current directory
    Filesystem& Filesystem::operator+=(Resource* res) {
        *m_current += res;
        return *this;
    }

    // change directory
    Directory* Filesystem::change_directory(const std::string& name) {

        if (name.empty()) {
            m_current = m_root;
            return m_current;
        }

        Resource* found = m_current->find(name);

        if (!found || found->type() != NodeType::DIR) {
            throw std::invalid_argument("Cannot change directory! " + name + " not found!");
        }

        m_current = dynamic_cast<Directory*>(found);
        return m_current;
    }

    // getter
    Directory* Filesystem::get_current_directory() const {
        return m_current;
    }

}