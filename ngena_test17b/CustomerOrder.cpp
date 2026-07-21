#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca
{
    size_t CustomerOrder::m_widthField = 0;

    /******************************************************
    * A customer 1-argument constructor that takes a
    * reference to an unmodifiable string. This constructor
    * uses a local Utilities object to extract the tokens from
    * the string and populate the current instance. The field
    * in the strings are
    * -> Customer Name
    * -> Order Name
    * -> the list of items making up the order (at least on item)
    * After finishing extraction, this constructor updates 
    * CustomerORder::m_widthField if the current value is smaller
    * that the value stored in Utilities::m_widthField
    ********************************************************/
    CustomerOrder::CustomerOrder(const std::string& record)
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(record, next_pos, more);
        if (more) {
            m_product = util.extractToken(record, next_pos, more);
        }

        // Temporary container to accumulate items for dynamic allocation
        std::vector<Item*> items;
        while (more) {
            std::string itemName = util.extractToken(record, next_pos, more);
            if (!itemName.empty()) {
                items.push_back(new Item(itemName));
            }
        }

        m_cntItem = items.size();
        m_listItem = new Item*[m_cntItem];
        for (size_t i = 0; i < m_cntItem; ++i) {
            m_listItem[i] = items[i];
        }

        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }
    }

    //move ops
    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
    {
        *this = std::move(other);
    }

    //move ops
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
    {
        if (this != &other) {
            // Clean up existing resources
            if (m_listItem) {
                for (size_t i = 0; i < m_cntItem; ++i) {
                    delete m_lstItem[i];
                }
                delete[] m_lstItem;
            }

            // Steal state from other
            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_listItem = other.m_listItem;

            // Reset source object
            other.m_cntItem = 0;
            other.m_listItem = nullptr;
        }
        return *this;
    }

    //destructor
    CustomerOrder::~CustomerOrder()
    {
        if (m_listItem) {
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
        }
    }

    //returns true if all items in the order have been filled
    bool CustomerOrder::isOrderFilled() const
    {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_listItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    //returns true if all items specified by itemName have been filled
    //If the item doesn't exist in the order, this query returns true
    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_listItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    /*******************************************************
    * This modifier fills one item in the current order that
    * the Station specified in the first parameter handles
    * - if the order doesn't contain the item handled, 
    * this function does nothing
    * - If the order contains items handled, and the 
    * Station's inventory contains at least one item, 
    * this function fills the order with one single item.
    *  It subtracts 1 from the inventory and updates 
    * Item::m_serialNumber and Item::m_isFilled. I
    * t also prints the message     
    * Filled NAME, PRODUCT [ITEM_NAME].
    * 
    * - if the order contains items handled but unfilled, 
    * and the inventory is empty, this function prints the
    *  message     Unable to fill NAME, PRODUCT [ITEM_NAME].
    * - all messages printed are terminated by an endline
    ********************************************************/
    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_listItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                    break; // Fill ONLY ONE item per station call
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                }
            }
        }
    }

    /*********************************************************
    * this query displays the state of the current object
    * 
    * CUSTOMER_NAME - PRODUCT
    * [SERIAL] ITEM_NAME - STATUS
    * [SERIAL] ITEM_NAME - STATUS
    * ...
    * 
    * SERIAL - a field of width 6
    * ITEM_NAME - a field of size m_widthField
    * STATUS is either FILLED or TO BE FILLED
    * you must use IO manipulators to format this output
    **********************************************************/
    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << "\n";
        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_listItem[i]->m_serialNumber << "] ";
            os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_listItem[i]->m_itemName << " - ";
            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << "\n";
        }
    }
}