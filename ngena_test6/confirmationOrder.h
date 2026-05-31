#ifndef SENECA_CONFIRMATIONORDER_H
#define SENECA_CONFIRMATIONORDER_H

#include <iostream>
#include "toy.h"



namespace seneca {
    /***************************************************************
    * ConfrimationOrder -> USES AGGREGATION
    * Only stores addresses
    * Purpose of the class is to contact the parents of the
    * children who want to shop and retreive approval before placing
    * an order
    *****************************************************************/
    class ConfirmationOrder
    {
        const Toy** m_toys{};
        size_t m_numToys{};
    public:
        //default constructor
        ConfirmationOrder() = default;

        //copy constructor
        ConfirmationOrder(const ConfirmationOrder& src);

        //copy assignment operator
        ConfirmationOrder& operator=(const ConfirmationOrder& src);

        // move constructor
        ConfirmationOrder(ConfirmationOrder&& src) noexcept;


        //move assignment operator
        ConfirmationOrder& operator=(ConfirmationOrder&& src) noexcept;

        //desrtuctor
        ~ConfirmationOrder();


        //add toy address
        ConfirmationOrder& operator+=(const Tpy& toy);

        //remove toy address
        ConfirmationOrder& operator-=(const Toy& toy);

        //output helper
        friend std::ostream& operator<<(
            std::ostream& os,
            const ConfirmationOrder& order
            );

    };

}
#endif
