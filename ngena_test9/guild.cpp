#include "guild.h"

namespace seneca {
    //creates a guild with the name specified as parameter
    Guild::Guild(const char* name) : m_name(name) {}

    //destructor
    Guild::~Guild() { delete[] m_members; }

    /***************************************************
    * adds the character received as parameter to guild
    * ONLY if it's not already in guild
    * Resizes array if necessary
    * if not already in guid increase max health of character by 300 points
    ****************************************************/
    void Guild::addMember(Character* c) {
        for(size_t i = 0; i < m_size; ++i) if(m_members[i] == c) return;
        
        c->setHealthMax(c->getHealthMax() + 300);
        c->setHealth(c->getHealthMax());
        
        Character** temp = new Character*[m_size + 1];
        for(size_t i = 0; i < m_size; ++i) temp[i] = m_members[i];
        temp[m_size++] = c;
        delete[] m_members;
        m_members = temp;
    }

    /*************************************************
    * removeMember() searches the guild for a character
    * with name received as parameter and removes it
    * if found in guild, reduce max health by 300
    **************************************************/
    void Guild::removeMember(const std::string& name) {
        for(size_t i = 0; i < m_size; ++i) {
            if(m_members[i]->getName() == name) {
                m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
                // Shift elements
                for(size_t j = i; j < m_size - 1; ++j) m_members[j] = m_members[j+1];
                m_size--;
                break;
            }
        }
    }

    //returns character at parameter specified index
    Character* Guild::operator[](size_t idx) const {
        return (idx < m_size) ? m_members[idx] : nullptr;
    }

    /****************************************************
    * showMembers() prints to the screen the character at 
    * index specified by parameter
    * -> or null if out of bounds
    * [FORMAT]:
    * [Guild] GUILD_NAME<endl>
    *    1: FIRST_CHARACTER<endl>
    *    2: SECOND_CHARACTER<endl>
    *    3: THIRD_CHARACTER<endl>
    *    ...
    * *
    * uses operator<< defined for Character class to print
    * single character
    * print "No guild.<endl> if empty state
    *****************************************************/
    void Guild::showMembers() const {
        if(m_size == 0) { std::cout << "No guild." << std::endl; return; }
        std::cout << "[Guild] " << m_name << std::endl;
        for(size_t i = 0; i < m_size; ++i) 
            std::cout << "    " << i+1 << ": " << *m_members[i] << std::endl;
    }

    // --> Copy Constructor
    Guild::Guild(const Guild& other) {
        m_size = other.m_size;
        m_name = other.m_name;
        if (other.m_members) {
            m_members = new Character*[m_size];
            for (size_t i = 0; i < m_size; ++i)
               m_members[i] = other.m_members[i]; //copy pointer
        }
    }

    //-> Copy Assignment
    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            delete[] m_members;
            m_size = other.m_size;
            m_name = other.m_name;
            m_members = nullptr;

            if (other.m_members) {
                m_members = new Character*[m_size];
                for (size_t i = 0; i < m_size; ++i)
                   m_members[i] = other.m_members[i];
            }
        }
        return *this;
    }

    Guild::Guild(Guild&& other) noexcept : m_members(nullptr), m_size(0) {
        *this = std::move(other);
    }

    //-> Move Assignmentt
    Guild& Guild::operator=(Guild&& other) noexcept {
        if (this != &other) {
            delete[] m_members;
            m_members = other.m_members;
            m_size = other.m_size;
            m_name = std::move(other.m_name);

            other.m_members = nullptr;
            other.m_size = 0;
        }
        return *this;
    }
}