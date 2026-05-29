#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <iostream> //needed???
#include <string> //???

namespace seneca {
    /*******************************************************
    * ->Toy Module includes the definition of a class that manages
    * info about single toy
    * id, name, number of items, price, harmonized sales tax
    ********************************************************/
    class Toy {
        unsigned int m_id{};
        std::string m_name{};
        unsigned int m_numItems{};
        double m_price{};

        static constexpr double HST = 0.13;
        
    public:
       Toy() = default; //default constructor

       //constructor that parses a string
       Toy(const std::string& toy);

       //modifier
       void update(int numItems);


       //output helper
       friend std::ostream& operator<<(std::ostream& os, const Toy& toy);
       
    }

}
#endif
