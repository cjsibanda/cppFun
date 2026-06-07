#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include <string>
#include "character.h"

namespace seneca {
    class Team {
        Character** m_members = nullptr;
        size_t m_size = 0;
        std::string m_name;
    public:
        Team(const char* name);
        //Rule of 5
        ~Team();
        Team(const Team& other);
        Team& operator=(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;

        void addMember(const Character* c);
        void removeMember(const std::string& name);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif