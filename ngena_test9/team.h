#include <string>
#include "character.h"

namespace seneca {
    /************************************************************* 
    * Team manages a dynamically allocated collection of characters
    * class should work wity an array of pointers to Character
    * -> stores the address of the array and a string with name of team
    * Team is in COMPOSITION relationship with character
    **************************************************************/
    class Team {
        Character** m_members = nullptr;
        size_t m_size = 0;
        std::string m_name;
    public:
        Team(const char* name) : m_name(name) {}
        // Rule of 5 Implementation
        ~Team() { for(size_t i=0; i<m_size; ++i) delete m_members[i]; delete[] m_members; }
        // Implement Copy/Move constructors and assignment operators here
        //rule of 5
        
        // adds the character received as parameter
        //ONLY if team doesn't have character with the same name
        //resize the array if necessary
        void addMember(const Character* c) {
            for(size_t i=0; i<m_size; ++i) if(m_members[i]->getName() == c->getName()) return;
            Character** temp = new Character*[m_size + 1];
            for(size_t i=0; i<m_size; ++i) temp[i] = m_members[i];
            temp[m_size++] = c->clone();
            delete[] m_members;
            m_members = temp;
        }

        //need remove member
 
        /***************************************************** 
        *
        *prints to the screen the content of the current object
        *uses the format...
        * [Team] TEAM_NAME<endl>
        *   1: FIRST_CHARACTER<endl>
        *   2: SECOND_CHARACTER<endl>
        *   3: THIRD_CHARACTER<endl>
        *    ...
        ******************************************************/
        void showMembers() const {
            if(m_size == 0) { std::cout << "No team." << std::endl; return; }
            std::cout << "[Team] " << m_name << std::endl;
            for(size_t i=0; i<m_size; ++i) std::cout << "    " << i+1 << ": " << *m_members[i] << std::endl;
        }
    };
}