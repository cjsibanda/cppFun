#include <cstring>
#include "FoodOrder.h"
using namespace std;


FoodOrder::FoodOrder() {
   return *this; //this&that = 0; ??
}


/*
--> to be continued

*/

/*
read(): a modifier that recieces an istream reference
*/
void FoodOrder::read(istream& is) {
  string m_name;  //will hold the Customer name
  string m_description;  //will hold the order desccription
  double m_price; //will hold the price

  cout  << "Customer Name : ";
  is >> m_name;
  cout << "Order Description : ";
  is >> m_description;
  cout << " Price" ;
  is >> m_price;
  // some logic here
  // do that

  //construct a temporary Food Order
  //FoodOrder temp(name, description, price);
  // if the data is valid, the temporary object into the current object
  // do that here...
}

void FoodOrder::display(ostream& os) const {
  //logic here
}