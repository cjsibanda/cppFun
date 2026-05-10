#include <iostream>
#include <iomanip>
#include <fstream>
#include "FoodOrder.h"
#include "FoodOrder.h"

// Cheching if header guards exist and follow convention.
#ifndef SENECA_FOODORDER_H
    #error "The header guard for 'FoodOrder.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

/* input file format: a comma separated set of fields with a consistent format of
<Order Tag>,<Customer Name>,<Order Description>,<Price>,<Daily Special Status>

<Order Tag> can be one of:
	I - In house order
	D - Delivery order

<Daily Special Status> can be one of:
	Y - Is a daily special
	N - Is not a daily special
*/

// TODO: write the prototype for the main function
//         to accept command line arguments
int main(int argc, char* argv[])
{
	/////////////////////////////////////////////////////
    // changed this
	///////////////////////////////////////////////////
	std::cout << "Command Line:\n";
    std::cout << "--------------------------\n";
    // FIXED: Correctly display the arguments starting from 1
    for (int i = 0; i < argc; ++i) {
        std::cout << std::setw(3) << std::right << i + 1 << ": " << argv[i] << std::endl;
    }
    std::cout << "--------------------------\n\n";

    seneca::FoodOrder recordedDeliveryOrders[10]; // Increased size slightly to be safe
    size_t numDeliveries = 0;
    seneca::FoodOrder currentOrder;

    for (int day = 1; day < argc; ++day) {
        if (day == 1) {
            g_taxrate = 0.13;
            g_dailydiscount = 1.15;
        } else {
            g_taxrate = 0.14;
            g_dailydiscount = 1.20;
        }

        std::cout << "--------------------\n";
        std::cout << "    Day " << day << '\n';
        std::cout << "--------------------\n";
        std::cout << "Name          |Order Description        |Price w/Tax |Special Price" << std::endl;

        std::ifstream in(argv[day]);
        if (!in.is_open()) {
            std::cout << "Cannot open file [" << argv[day] << "]. Ignoring it!\n";
            continue; 
        }

        char ordertag = '\0';
        while (in) {
            in >> ordertag;
            if (in.fail()) break;
            in.ignore(); // skip comma

            currentOrder.read(in);

            if (ordertag == 'I') {
                currentOrder.display();
            } else if (ordertag == 'D') {
                // Record deliveries and display
                recordedDeliveryOrders[numDeliveries++] = currentOrder;
                currentOrder.display();
            }
        }
    }
	/////////////////////////////////////////

	// print the recorded orders
	std::cout << "--------------------\n";
	std::cout << "Recorded Delivery Food Orders\n";
	std::cout << "--------------------\n";
	std::cout << "Name          |Order Description        |Price w/Tax |Special Price" << std::endl;
	for (auto i = 0u; i < numDeliveries; ++i)
		recordedDeliveryOrders[i].display();
	std::cout << "--------------------\n";

	return cout;
}