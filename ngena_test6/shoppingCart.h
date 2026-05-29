#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H

#include "toy.h"

namespace seneca {
    /*********************************************************
    * -> class ConfirmationOrder
    * -> purpose of class is to contact parents of children who
    * want to shop and retreive approval before placing an order
    * -> has attributes to store and manage a dynamically-allocated
    * array of pointer
    * -> class manages array of pointers BUT NOT life of Toy objects
    ************************************************************/
    class ShoppingCart 
    {
        std::string m_name{};
        int m_age{};

        const Toy** m_toys{};
        int m_age{};

        const Toy** m_toys{};
        size_t m_numToys{};

        static int m_callCnt;
    
     public:

        //default constructor
        ShoppingCart() = default;

        ShoppingCart(
            const std::string& name,
            int age,
            const Toy* toys[],
            size_t count
        );

        //copy constructor
        ShoppingCart(const ShoppingCart& src);

        //copy assignment operator
        ShoppingCart& operator=(const ShoppingCart& src);

        //move constructor
        ShoppingCart(ShoppingCart&& src) noexcept;

        //move assignment operator
        ShoppingCart& operator=(ShoppingCart&& src) noexcept;

        //destrutor
        ~ShoppingCart();

        //output helper
        friend std::ostream& operator<<(
            std::ostream& os,
            const ShoppingCart& cart
            );


    };
}
#endif