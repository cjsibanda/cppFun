#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H

namespace seneca {
    class ShoppingCart 
    {
     /*************************************
     * "Rain does not fall on one roof alone"
     **************************************/
     public:
        ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count);
    };
}
#endif