#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include "characterTpl.h"
#include "weapons.h"

namespace seneca {
    /*****************************************************
    * Rogue is derived from CharacterTpL<T>
    * concrete class implementing babarian-specific logic
    * For Template paramerters:
    * [T]: the type of object storing the healty
    * FirstAbility_t: the type implementing the first special ability
    * SecondAbility_t: the type implmenting second ability
    *****************************************************/
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense; //represents basic defense
        int m_baseAttack; //represents basick attack power
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        seneca::Dagger m_weapon; //?? (just say Dagger?)
    public:
        //initializes to values in parameters
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {}


            
        int getAttackAmnt() const override { return m_baseAttack + 2 * static_cast<int>(static_cast<double>(m_weapon)); }
        int getDefenseAmnt() const override { return m_baseDefense; }

        // dynamically creates a copy of the current instance
        // returns its address to the client
        Character* clone() const override { return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this); }

        //Attacks the enemy received in parameter
        // inflicts damage to enemy
        //uses first special ability fo activate and benefical effects on self
        void attack(Character* enemy) override {
            std::cout << getName() << " is attacking " << enemy->getName() << "." << std::endl;
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);
            int dmg = getAttackAmnt();
            m_firstAbility.transformDamageDealt(dmg);
            m_secondAbility.transformDamageDealt(dmg);
            std::cout << "    Rogue deals " << dmg << " melee damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        //override
        //
        void takeDamage(int dmg) override {
            std::cout << getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;
            int actual = (dmg - getDefenseAmnt() < 0) ? 0 : dmg - getDefenseAmnt();
            m_firstAbility.transformDamageReceived(actual);
            m_secondAbility.transformDamageReceived(actual);
            CharacterTpl<T>::takeDamage(actual);
        }
    };
}
#endif