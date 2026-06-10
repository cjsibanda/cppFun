#include <iostream>
#include <string>
#include <stdexcept>

/***************************************************
* ----- TEMPLATES 1 ----
* 1. Create a family of functions (a template function)
* that checks how many times a certain item appears in array.
* The function should return the number of occurences. Specializes
* std::string to check how many times the first letter of a string
* appears in all strings from in the array.
****************************************************/
//General template function
template <typename T>
int countOccurences(T array[], int size, T item) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] == item) {
            count++;
        }
    }
    return count;
}

//Specialization for std::string
template <>
int countOccurences<std::string array[], int size, std::string item> {
   int count = 0;
   /* ?????*/
   return count++;
}

/***********************************************************
* --- TEMPLATES 9 -----
* Create a family of functions (a template function) that
* finds the second biggest element in an array received as a 
* parameter. If there is no such element (all elements are equal,
* array contains a single element), raise an exception to inform
the client. Specialize char* to compare strings by content.
************************************************************/
template <typename T>
T secondBiggest(T array[], int size) {
    if (size < 2) throw std::runtime_error("Not enough elements");

    T max = array[0];
    T second = array[0];
    bool found = false 

    for (int i = 1; i < size; ++i) {
        if (array[i] > max) {
            second = max;
            max = array[i];
            found = true;
        } else if (array[i] < max && (array[i] > second || !found)) {
            second = array[i];
            found = true;
        }
    }

    if (second == max) throw std::runtime_error("No second biggest");
    return second;
}

//Specialization for const char*
template <>
const char* secondBiggest<const char*>(const char* array[], int size){
    //////
    ///////
    // if exception?
    return second;
}


/****************************************************
* --- CLASSES (RULE-OF-5, TYPE MEMBERS)
Create a family of class named Collection (a template class) that manages a dynamically allocated collection of items of any type.  The class should support the following operations:
  - create an empty collection
  - rule-of-5
  - add an item
  - remove an item
  - retrieve the item at a specified index
  - modify the item from a specified index
  - print the content of the collection to screen
  - remove all items
  - remove all items that match a certain condition (a lambda expression received from the client as a parameter)
  - create a new collection that contains only items that match a certain condition (a lambda expression received from the client as a parameter)
The class should use exceptions to inform the client when an operation cannot be completed (e.g., bad parameters)

You are provided with the following code
----------------------------------------------
enum class ItemType
{
  Clothing,
  Electronics,
  Appliance,
  Book,
  Movie,
  Computers,
  Tools,
  Gaming,
  Sports
}
class Item
{
  const ItemType m_category;
  std::string m_description{};
  std::string m_id{};
  double m_price{};
  double m_discount{};// a number in the interval [0, 1]
  // ...
}
class ShoppingCart
{
  Item* m_pItems{}; // a dynamically allocated array of items in the shopping cart
  size_t m_cnt{};
  // ...
}
-----------------------------------------------

Add to the two classes members to support the following operations:
  - ShoppingCart
    - add items to the shopping cart
    - remove items from the shopping cart
    - rule-of-5 for the shopping cart
    - remove from the shopping cart all items from a specified category (e.g., ItemType::Tools)
    - remove from the shopping cart all items that don’t have a discount (discount is 0)
    - update the discount on all items in a shopping cart that belong to a certain category (e.g., ItemType::Book)
    - remove from the shopping cart all items that match a predicate received as a parameter (this is a lambda expression)
    - print to screen the content of the shopping cart, formatted as a table

- Item
    - in a class variable in class Item, count how many objects in the category ItemType::Gaming exist in the program (created but not yet destroyed)
    - in a class variable in class Item, count how many discounted objects exists in the program (created but not yet destroyed). Note that the m_discount attribute can change during the lifetime of an object; this counter must be updated when an item becomes discounted or is not discounted anymore.
    - add class functions to access the value of these counters

- Derived class
    - create a new class derived from ShoppingCart that doesn’t allow multiple items with the same ID (override the relevant functions).
    - add to this class an attribute of type char* that is a user-provided-name for the shopping cart (e.g., Gifts for John, Party for Alice, Home improvement, Trip to Europe) – this is a resource and should be managed by the class: implement rule-of-5.

All attributes must be private (make functions to access them); do not use global variables.

*****************************************************/


//Template Class for Collection
template<typename T>
class Collection {
    T* m_data{};
    size_t m_size{};
public:
   //1. create an empty collection
   Collection() = default;

   //2. Rule of 5...

   //Destructor
   ~Collection() {
    delete[] m_data;
   }

   //copy contructor
   Collection(const Collection& other) {
    m_size = other.m_size;
    m_data = new T[m_size];
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
   }

   // -> Copy Assignment Operator 
   Collection operator=(const Collection& other) {
    if (this != &other) {
        delete[] m_data;
        m_size = other.m_size;
        m_data = other.m_size;
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }
    return *this;
   }

   //-> Move constructor
   Collection(Collection&& other) noexcept : m_data(other.m_data), m_size(other.m_size) {
    other.m_data = nullptr;
    other.m_size = 0;
   }

   //move construction op
   Collection& operator=(Collection&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        other.m_data = nullptr;
        other.m_size = 0;
    }
    return *this;
   }

   //Add an item
   void add(const T& item) {
    T* temp = new T[m_size + 1];
    for (size_t i = 0; i < m_size; ++i) temp[i] = m_data[i];
    temp[m_size] = item;
    delete[] m_data;
    m_data = temp;
    m_size++;
   }
   
   //Remove an item (by index for simplicity)
   voic remove(size_t index) {
    if (index >= m_size) throw std::out_of_range("out of bounds");
    T* temp = new T[m_size - 1];
    for (size_t i = 0, j = 0; i < m_size; ++i) {
        if (i != index) temp[j++] = m_data[i];
    }
    delete[] m_data;
    m_data = temp;
    m_size--;
   }

   //Retrieve item at index
   T& retrieve(size_t index) const {
    if (index >= m_size) throw std::out_of_range("Index out of range");
    return m_data[index];
   }

   // Modify item at index
   void modify(size_t index, const T& newItem) {
    if (index >= m_size) throw std::out_of_range("Inex out of bounds");
    m_data[index] = newItem;
   }
  
    //Print content
    void print() const {
        for(size_t i = 0; i < m_size; ++i) {
            std::cout << m_data[i] << std::endl;
        }
    }

    //Remove all items
    void removeAll() {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
    }

    //Remove matching a condition (Lambda function)
    //????
    void removeIf(std::function<bool(const T&)> condition) {
        size_t keepCount = 0;
        for (size_t i = 0; i < m_size; ++i) {
            if(!condition(m_data[i])) keepCount++;
        }

        T* temp = new T[keepCount];
        for (size_t i = 0, j = 0; i < m_size; ++i) {
            if (!condition(m_data[i])) temp[j++] = m_data[i];
        }
        delete[] m_data;
        m_data = temp;
        m_size = keepcount;
    }

    //Create a new collection matching Lambda
    Collection<T> create(std::function<bool(const T&)> condition) const{
        Collection<T> result;
        for (size_t i = 0; i < m_size; ++i) {
            if (condition(m_data[i])) {
                result.add(m_data[i]);
            }
        }
        return result;
    }
}




int main() {

}