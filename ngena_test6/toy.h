#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <iostream> //needed???
#include <string> //???

namespace seneca {
    class Toy {
        /*************************************
        * If you want to go fast, go alone.
        * If you want to go far, go together
        * I am because we are
        * Ubuntu
        *************************************/
    public:
       Toy() = default; //default constructor
       Toy(const std::string& toy);
       void update(int numItems);
       
    }

}
#endif
