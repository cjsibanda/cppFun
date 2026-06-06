#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"

namespace seneca {
    /**********************************************************
    * characterTpl Module is derived from Character
    *  -> it will add health and health manupulation functions
    * -> health can heave numerical type
    * 
    ***********************************************************/
    template <typename T> //T: the type of the object storing the health
    class CharacterTpl : public Character {
        int m_healthMax; //int represents max health character can have
        T m_health; //object of Type T represents current health 
    public:
        //custome constructor
        CharacterTpl(const char* name, int healthMax) 
            : Character(name), m_healthMax(healthMax) {
            m_health = healthMax;
        }

        //reduces the health by the value of parameter
        void takeDamage(int dmg) override {
            m_health -= dmg;
            if (getHealth() <= 0) {
                std::cout << getName() << " has been defeated!" << std::endl;
            } else {
                std::cout << getName() << " took " << dmg << " damage, " 
                          << getHealth() << " health remaining." << std::endl;
            }
        }

        // returns the current health
        // assumed the T supports conversion to int using static_cast
        int getHealth() const override { return static_cast<int>(m_health); }

        //returns current max health
        int getHealthMax() const override { return m_healthMax; }

        //set current health to value set in parameter
        void setHealth(int health) override { m_health = health; }

        //sets the max health and current health to parameter value
        void setHealthMax(int health) override {
            m_healthMax = health;
            setHealth(health);
        }
    };
}
#endif