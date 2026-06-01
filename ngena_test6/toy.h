#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <iostream> 
#include <string> 

namespace seneca {
    /*******************************************************
    * ->Toy Module includes the definition of a class that manages
    * info about single toy
    * id, name, number of items, price, harmonized sales tax
    ********************************************************/
    class Toy {
        unsigned int m_id{0};
        std::string m_name{};
        unsigned int m_num{0};
        double m_price{};

        static constexpr double hst = 0.13;

        void trim(std::string& str) const;
        
    public:
       Toy() = default; //default constructor

       //constructor that parses a string
       Toy(const std::string& toy);

       //modifier
       void update(int numItems) {m_num = numItems;};


       //output helper
       friend std::ostream& operator<<(std::ostream& os, const Toy& toy);
       
    };

}
#endif
