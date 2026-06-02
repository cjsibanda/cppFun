#include <utility>
#include <ostream>
#include "shoppingCart.h"

namespace seneca
{
    ShoppingCart::ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count)
    {
        m_name = name;
        m_age = age;
        m_count = count;
        m_toys = new const Toy*[m_count];
        for (auto i = 0u; i < m_count; ++i)
           m_toys[i] = new Toy(*toys[i]);
    }
    ShoppingCart::ShoppingCart(const ShoppingCart& src)
    {
        *this = src;
    }
    ShoppingCart& ShoppingCart::operator=(const ShoppingCart& src)
    {
        if (this != &src)
        {
            delete[] m_toys;
            m_name = src.m_name;
            m_age = src.m_age;
            m_count = src.m_count;

            if (m_count > 0)
            {
                m_toys = new const Toy*[m_count];
                for (auto i = 0u; i < m_count; ++i) {
                    m_toys[i] = src.m_toys[i];
                }
            }
            else {
                m_toys = nullptr;
            }
            
        }
        return *this;
    }
    //move constructor
    ShoppingCart::ShoppingCart(ShoppingCart&& src) noexcept
    {
        *this = std::move(src);
    }

    //Move assignement operator
    ShoppingCart& ShoppingCart::operator=(ShoppingCart&& src) noexcept
    {
        if (this != &src)
        {
            delete[] m_toys;
            m_count = src.m_count;
            m_name = src.m_name;
            m_age = src.m_age;

            m_toys = src.m_toys;
            src.m_count = 0;
            src.m_name = "";
            src.m_age = 0;
            src.m_toys = nullptr;
        }
        return *this;
    }
    ShoppingCart::~ShoppingCart()
    {
        delete[] m_toys;
    }

    std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart)
    {
        static size_t callCnt = 0;
        os << "----------------------\n";
        if (cart.m_name != "")
        {
            os << "Order " << ++callCnt << ": Shopping for " << cart.m_name << " "
               << cart.m_age << " years old (" << cart.m_count  << " toys)\n";
            os << "-----------------------------\n";
            if (cart.m_count == 0)
                  os << "Empty shopping cart!\n";
            for (auto i = 0u; i < cart.m_count; ++i)
                os << *cart.m_toys[i];   
        }
        else 
             os << "Order " << ++callCnt << ": This shooping cart is invalid.\n";
        os << "----------------------\n";
        return os;     
    }
}