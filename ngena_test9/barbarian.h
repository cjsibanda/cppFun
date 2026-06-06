#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include "characterTpl.h"
#include "weapons.h"
#include <iostream>

namespace seneca {
    /****************************************************************
    * Barbarian is derived from CharacterTpL<T>
    * class is a concrete class implementing barbarian specific logic
    ******************************************************************/
   // T: the type of object storing the health
   //Ability_t: the type implementing the special abilities 
   //Weapon_h: the type implementing weapons barbarian handles
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense; //int represents basic defense of character
        int m_baseAttack; // int represents basic attack power of character
        Ability_t m_ability; // special abilities
        Weapon_t m_weapon[2];
    public:
        //initializes new object to values recieved as parameters
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, 
                  Weapon_t w1, Weapon_t w2) 
            : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), 
              m_baseDefense(baseDefense) {
            m_weapon[0] = w1; m_weapon[1] = w2;
        }

        //return damage that character can do in attack
        // using BASE_ATTACK formula
        int getAttackAmnt() const override {
            return m_baseAttack + static_cast<double>(m_weapon[0]) + static_cast<double>(m_weapon[1]);
        }

        //return base defense value
        int getDefenseAmnt() const override { return m_baseDefense; }

        //creates a copy of the current instance
        //returns address to client
        Character* clone() const override { return new Barbarian<T, Ability_t, Weapon_t>(*this); }

        //attacks the enemy received as parameter, inflicts damage
        void attack(Character* enemy) override {
            std::cout << getName() << " is attacking " << enemy->getName() << "." << std::endl;
            m_ability.useAbility(this);
            int dmg = getAttackAmnt();
            m_ability.transformDamageDealt(dmg);
            std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        //other character inflicts damage in parameter amount
        void takeDamage(int dmg) override {
            std::cout << getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << getDefenseAmnt() 
                      << ". Reducing damage received." << std::endl;
            
            int actualDamage = (dmg - getDefenseAmnt() < 0) ? 0 : dmg - getDefenseAmnt();
            m_ability.transformDamageReceived(actualDamage);
            CharacterTpl<T>::takeDamage(actualDamage);
        }
    };
}
#endif