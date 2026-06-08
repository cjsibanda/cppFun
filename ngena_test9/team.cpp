#include "team.h"
#include <iostream>

namespace seneca {
    Team::Team(const char* name) : m_name(name) {}

    

    
    Team::Team(const Team& other) { *this = other; }

    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            //1. clean up
            for (size_t i = 0; i < m_size; ++i) delete m_members[i];
            delete[] m_members;

            //2. Shallow copy simple members
            m_size = other.m_size;
            m_name = other.m_name;
            
            //3. Deep copy the array
            m_members = new Character*[m_size];
            for (size_t i = 0; i < m_size; ++i)
                m_members[i] = other.m_members[i]->clone();
        }
        return *this;
    }

    Character* Team::operator[](size_t idx) const {
        return (idx < m_size) ? m_members[idx] : nullptr;
    }

    void Team::removeMember(const std::string& name) {
        int index = -1;
        for(size_t i = 0; i < m_size; ++i) 
        {
            if(m_members[i]->getName() == name) {
                index = static_cast<int>(i);
                break;
            }
        }
        if(index != -1) 
        {
            delete m_members[index]; //Free memory
            //Shift the remaining pointers
            for(size_t i = index; i < m_size - 1; ++i) 
            {
                m_members[i] = m_members[i + 1];
            }
            m_size--;
        }

    }


    //move constructor
    Team::Team(Team&& other) noexcept : m_members(nullptr), m_size(0) {
        *this = std::move(other); //<--???
    }

    //move assignment operator
    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) delete m_members[i];
            delete[] m_members;
            m_members = other.m_members;
            m_size = other.m_size;
            m_name = std::move(other.m_name);
            other.m_members = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    //destructor
    Team::~Team() {
        for (size_t i = 0; i < m_size; ++i) delete m_members[i];
        delete[] m_members;
    }

    //addMember
    void Team::addMember(const Character* c) {
        for(size_t i = 0; i < m_size; ++i)
           if(m_members[i]->getName() == c->getName())
           return;

        Character** temp = new Character*[m_size + 1];
        for(size_t i = 0; i < m_size; ++i) temp[i] = m_members[i];
        temp[m_size++] = c->clone();
        delete[] m_members;
        m_members = temp;
    }

    
    void Team::showMembers() const {
    if(m_size == 0) {
        std::cout << "No Team." << std::endl;
        return;
    }
    std::cout << "[Team] " << m_name << std::endl;
    for(size_t i = 0; i < m_size; ++i) {
        std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
      }
    }
    
}