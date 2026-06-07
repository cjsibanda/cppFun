#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>

namespace seneca {
    class Guild {
        Character** m_members = nullptr;
        size_t m_size = 0;
        std::string m_name;
    public:
        Guild(const char* name) : m_name(name) {}
        ~Guild() { delete[] m_members; }

        void addMember(Character* c) {
            for(size_t i=0; i<m_size; ++i) if(m_members[i] == c) return;
            c->setHealthMax(c->getHealthMax() + 300);
            c->setHealth(c->getHealthMax());
            Character** temp = new Character*[m_size + 1];
            for(size_t i=0; i<m_size; ++i) temp[i] = m_members[i];
            temp[m_size++] = c;
            delete[] m_members;
            m_members = temp;
        }

        void removeMember(const std::string& name) {
            for(size_t i=0; i<m_size; ++i) {
                if(m_members[i]->getName() == name) {
                    m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
                    // Shift and resize logic...
                }
            }
        }

        void showMembers() const {
            if(m_size == 0) { std::cout << "No guild." << std::endl; return; }
            std::cout << "[Guild] " << m_name << std::endl;
            for(size_t i=0; i<m_size; ++i) std::cout << "    " << i+1 << ": " << *m_members[i] << std::endl;
        }
    };
}
#endif //SENECA_GUILD_H