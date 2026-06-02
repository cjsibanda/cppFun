#include <utility>
#include "confirmationOrder.h"

namespace seneca
{
//copy constructor
ConfirmationOrder::ConfirmationOrder(const ConfirmationOrder& src)
{
    *this = src;
}

//copy assignment op
ConfirmationOrder& ConfirmationOrder::operator=(const ConfirmationOrder& src){
        if (this != &src)
        {
            delete[] this->m_toys;

            this->m_count = src.m_count;

            if (this->m_count > 0)
            {
               this->m_toys = new const Toy * [m_count];
               for (auto i = 0u; i < this->m_count; ++i)
                      this->m_toys[i] = src.m_toys[i];
            }
            else
                this->m_toys = nullptr;
        }
        return *this;
}

//move constructor
ConfirmationOrder::ConfirmationOrder(ConfirmationOrder&& src) noexcept
{
    *this = std::move(src);
}

//move assignment op
ConfirmationOrder& ConfirmationOrder::operator=(ConfirmationOrder&& src) noexcept
{
    if (this != &src)
    {
        delete[] m_toys;

        m_count = src.m_count;
        m_toys = src.m_toys;
        src.m_toys = nullptr;
        src.m_count = 0;
    }
    return *this;
}

//Destructor
ConfirmationOrder::~ConfirmationOrder()
{
    delete[] m_toys;
}

/// 
ConfirmationOrder& ConfirmationOrder::operator+=(const Toy& toy)
{
    bool found = false;

    for (auto i = 0u; i < m_count && found == false; ++i)
    {
        if (&toy == m_toys[i])
        {
            found = true;
        }
    }

    if (found == false)
    {
        const Toy** temp = nullptr;

        temp = new const Toy*[m_count + 1];

        for (auto i = 0u; i < m_count; ++i)
        {
            temp[i] = m_toys[i];
        }

        temp[m_count] = &toy;

        ++m_count;

        delete[] m_toys;
        m_toys = temp;
    }

    return *this;
}
/////

ConfirmationOrder& ConfirmationOrder::operator-=(const Toy& toy)
{
    auto id = 0u;
    for (; id < m_count; ++id)
        if (&toy == m_toys[id])
            break;
     
    if (id < m_count)
    {
        const Toy** temp = nullptr;
        if (m_count > 1u)
        {
            //-> to resize
            temp = new const Toy * [m_count - 1];
            for (auto i = 0u; i < id; ++i)
                temp[i] = m_toys[i];
            for (auto i = id; i < m_count - 1; ++i)
                temp[i] = m_toys[i + 1];
        }
        delete[] m_toys;
        m_toys = temp;
        --m_count;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order)
{
    os << "----------------------\n";
    os << "Confirmation to Send (" << order.m_count << " toys)\n";
    os << "----------------\n";
    if (order.m_count == 0)
        os << "There are no confirmations to send!\n";
    for (auto i = 0u; i < order.m_count; ++i)
          os << *(order.m_toys[i]);
    os << "------------------------\n";
    return os;
}

}
