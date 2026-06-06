#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include "characterTpl.h"
#include "health.h"

namespace seneca {
    /*********************************************************
    * Class Archer is derived from CharacterTpL 
    *-> all archers have super health
    * class in concrete and implements archer-specific logic
    **********************************************************/
   // Weapon_t: the type implementing the weapons the Barbariabn will handle
    template <typename Weapon_t> 
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_baseDefense; //represnts basic defense of character
        int m_baseAttack; //represents basic attack power of character
        Weapon_t m_weapon; //object represents weapon of character
    public:
        //initializes new object to values received as parameters
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax), 
              m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}

        //return damage character can do
        // uses formula
        int getAttackAmnt() const override { return static_cast<int>(1.3 * m_baseAttack); }

        //returns defense of character
        //uses formula
        int getDefenseAmnt() const override { return static_cast<int>(1.2 * m_baseDefense); }

        //dynamically creates a copy of the current instance 
        //returns address to the client
        Character* clone() const override { return new Archer<Weapon_t>(*this); }

        //attacks the enemy received as parameter
        //inflicts damage
        void attack(Character* enemy) override {
            std::cout << getName() << " is attacking " << enemy->getName() << "." << std::endl;
            int dmg = getAttackAmnt();
            std::cout << "    Archer deals " << dmg << " ranged damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        //other character does damage to archer
        //damaged specified by parameter dmg
        void takeDamage(int dmg) override {
            std::cout << getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;
            int actual = (dmg - getDefenseAmnt() < 0) ? 0 : dmg - getDefenseAmnt();
            CharacterTpl<seneca::SuperHealth>::takeDamage(actual);
        }
    };
}
#endif