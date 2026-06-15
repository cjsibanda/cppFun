//TEMPLATES 1

#include <iostream>
#include <string>

// General template function
template <typename T>
int countOccurrences(T array[], int size, T item) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] == item) {
            count++;
        }
    }
    return count;
}

// Specialization for std::string
template <>
int countOccurrences<std::string>(std::string array[], int size, std::string item) {
    int count = 0;
    // Check if the item string is not empty to avoid errors
    if (item.empty()) return 0;
    
    char target = item[0]; // The first letter to look for
    for (int i = 0; i < size; ++i) {
        if (!array[i].empty() && array[i][0] == target) {
            count++;
        }
    }
    return count;
}


//TEMPLATES 2
 --- TEMPLATES 9 -----
* Create a family of functions (a template function) that
* finds the second biggest element in an array received as a 
* parameter. If there is no such element (all elements are equal,
* array contains a single element), raise an exception to inform
the client. Specialize char* to compare strings by content.

/////////////////////

#include <iostream>
#include <cstring>
#include <stdexcept>

// General template
template <typename T>
T secondBiggest(T array[], int size) {
    if (size < 2) throw std::runtime_error("Not enough elements");

    T max = array[0];
    T second = array[0];
    bool found = false;

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

    if (second == max) throw std::runtime_error("No unique second biggest");
    return second;
}

// Specialization for const char*
template <>
const char* secondBiggest<const char*>(const char* array[], int size) {
    if (size < 2) throw std::runtime_error("Not enough elements");

    const char* max = array[0];
    const char* second = array[0];
    bool found = false;

    for (int i = 1; i < size; ++i) {
        if (std::strcmp(array[i], max) > 0) {
            second = max;
            max = array[i];
            found = true;
        } else if (std::strcmp(array[i], max) < 0 && (!found || std::strcmp(array[i], second) > 0)) {
            second = array[i];
            found = true;
        }
    }

    if (std::strcmp(second, max) == 0) throw std::runtime_error("No unique second biggest");
    return second;
}


//---------------------------------------
//RECURSIVE FUNCTIONS + ITERATIVE VERSIONS
//-----------------------------------------

//1. Print dots recursively


#include <iostream>
using namespace std;

void printDotsRec(int n, int i = 1)
{
    if (i > n) return;

    for (int j = 0; j < i; j++)
        cout << ".";

    cout << "\n";

    printDotsRec(n, i + 1);
}

//iTERATIVE


void printDotsIt(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
            cout << ".";
        cout << "\n";
    }
}

//2. Series: 1 + 2×2 + 3 + 2×4 + ...

int series1(int n)
{
    if (n == 1) return 1;

    if (n % 2 == 0)
        return 2 * n + series1(n - 1);
    else
        return n + series1(n - 1);
}

//ITERATIVE

int series1_it(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0) sum += 2 * i;
        else sum += i;
    }
    return sum;
}

//count 'A' IN String recursively

int countA(const std::string& s, int i = 0)
{
    if (i == (int)s.size()) return 0;

    return (s[i] == 'a' ? 1 : 0) + countA(s, i + 1);
}

//iterative

int countA_it(const std::string& s)
{
    int count = 0;
    for (char c : s)
        if (c == 'a') count++;
    return count;
}

//Sum Array of Doubles

int countA_it(const std::string& s)
{
    int count = 0;
    for (char c : s)
        if (c == 'a') count++;
    return count;
}

//Iterative

double sumArray_it(const double arr[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

//count even numbers in int array
double sumArray_it(const double arr[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

//Iterative:

int countEven(const int arr[], int n)
{
    if (n == 0) return 0;

    return (arr[n - 1] % 2 == 0)
        + countEven(arr, n - 1);
}

//Replace space with '.'
void replaceSpaces(std::string& s, int i = 0)
{
    if (i == (int)s.size()) return;

    if (s[i] == ' ')
        s[i] = '.';

    replaceSpaces(s, i + 1);
}

//Iterative

void replaceSpaces_it(std::string& s)
{
    for (char& c : s)
        if (c == ' ')
            c = '.';
}


//8 Replace negatives with abosultue value (float array)

void absArray(float arr[], int n)
{
    if (n == 0) return;

    if (arr[n - 1] < 0)
        arr[n - 1] = -arr[n - 1];

    absArray(arr, n - 1);
}

//Iterative

void absArray_it(float arr[], int n)
{
    for (int i = 0; i < n; i++)
        if (arr[i] < 0)
            arr[i] = -arr[i];
}


//9 Count divisions by 2

void absArray_it(float arr[], int n)
{
    for (int i = 0; i < n; i++)
        if (arr[i] < 0)
            arr[i] = -arr[i];
}

//Iterative

int countDiv2(int n)
{
    if (n <= 0) return 0;
    if (n % 2 != 0) return 0;

    return 1 + countDiv2(n / 2);
}

//Print array with commas:

int countDiv2_it(int n)
{
    int count = 0;
    while (n > 0 && n % 2 == 0)
    {
        count++;
        n /= 2;
    }
    return count;
}

//Iterative:

void printArray_it(const int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i];
        if (i < n - 1) std::cout << ", ";
    }
}

//Return comma-seperated string


void printArray_it(const int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i];
        if (i < n - 1) std::cout << ", ";
    }
}

//Iterative

std::string arrayToString_it(const int arr[], int n)
{
    std::string result;

    for (int i = 0; i < n; i++)
    {
        result += std::to_string(arr[i]);
        if (i < n - 1)
            result += ", ";
    }

    return result;
}


//Time Recursive vs Iterative:
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

template<typename Func>
void timeFunc(Func f, const std::string& name)
{
    auto start = high_resolution_clock::now();

    for (int i = 0; i < 10000; i++)
        f();

    auto end = high_resolution_clock::now();

    cout << name << ": "
         << duration_cast<microseconds>(end - start).count()
         << " μs\n";
}

//Example

#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

template<typename Func>
void timeFunc(Func f, const std::string& name)
{
    auto start = high_resolution_clock::now();

    for (int i = 0; i < 10000; i++)
        f();

    auto end = high_resolution_clock::now();

    cout << name << ": "
         << duration_cast<microseconds>(end - start).count()
         << " μs\n";
}



////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////


//PART 1 : THE GENERIC COLLECTION TEMPLATE

//-------------------------------------------------
#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>
#include <iomanip>
#include <cstring>

// =======================================================================
// 1. TEMPLATE CLASS: Collection
// =======================================================================
template <typename T>
class Collection {
    T* m_data{};
    size_t m_size{};

public:
    // 1. Create an empty collection
    Collection() = default;

    // 2. Rule of 5
    ~Collection() { 
        delete[] m_data; 
    }

    Collection(const Collection& other) {
        m_size = other.m_size;
        m_data = new T[m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    Collection& operator=(const Collection& other) {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_data = new T[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    Collection(Collection&& other) noexcept : m_data(other.m_data), m_size(other.m_size) {
        other.m_data = nullptr;
        other.m_size = 0;
    }

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

    // 3. Add an item
    void add(const T& item) {
        T* temp = new T[m_size + 1];
        for (size_t i = 0; i < m_size; ++i) temp[i] = m_data[i];
        temp[m_size] = item;
        delete[] m_data;
        m_data = temp;
        m_size++;
    }

    // 4. Remove an item (by index for simplicity)
    void remove(size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of bounds");
        T* temp = new T[m_size - 1];
        for (size_t i = 0, j = 0; i < m_size; ++i) {
            if (i != index) temp[j++] = m_data[i];
        }
        delete[] m_data;
        m_data = temp;
        m_size--;
    }

    // 5. Retrieve item at index
    T& retrieve(size_t index) const {
        if (index >= m_size) throw std::out_of_range("Index out of bounds");
        return m_data[index];
    }

    // 6. Modify item at index
    void modify(size_t index, const T& newItem) {
        if (index >= m_size) throw std::out_of_range("Index out of bounds");
        m_data[index] = newItem;
    }

    // 7. Print content
    void print() const {
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << m_data[i] << std::endl;
        }
    }

    // 8. Remove all items
    void removeAll() {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
    }

    // 9. Remove matching a condition (Lambda)
    void removeIf(std::function<bool(const T&)> condition) {
        size_t keepCount = 0;
        for (size_t i = 0; i < m_size; ++i) {
            if (!condition(m_data[i])) keepCount++;
        }

        T* temp = new T[keepCount];
        for (size_t i = 0, j = 0; i < m_size; ++i) {
            if (!condition(m_data[i])) temp[j++] = m_data[i];
        }
        delete[] m_data;
        m_data = temp;
        m_size = keepCount;
    }

    // 10. Create new collection matching condition (Lambda)
    Collection<T> createIf(std::function<bool(const T&)> condition) const {
        Collection<T> result;
        for (size_t i = 0; i < m_size; ++i) {
            if (condition(m_data[i])) {
                result.add(m_data[i]);
            }
        }
        return result;
    }
};
//--------------------------------------------------------------

//PART 2: ItemType and Item Classes

//------------------------------------------------------------
// =======================================================================
// 2. ENUM AND ITEM CLASS
// =======================================================================
enum class ItemType {
    Clothing, Electronics, Appliance, Book, Movie, Computers, Tools, Gaming, Sports
};

class Item {
    ItemType m_category{};
    std::string m_description{};
    std::string m_id{};
    double m_price{};
    double m_discount{}; // [0, 1]

    // Static counters
    static int s_gamingCount;
    static int s_discountedCount;

    // Helper to manage counters safely
    void updateCounters(int modifier) {
        if (m_category == ItemType::Gaming) s_gamingCount += modifier;
        if (m_discount > 0.0) s_discountedCount += modifier;
    }

public:
    Item() = default;

    Item(ItemType cat, std::string desc, std::string id, double price, double discount)
        : m_category(cat), m_description(desc), m_id(id), m_price(price), m_discount(discount) {
        if (discount < 0.0 || discount > 1.0) throw std::invalid_argument("Discount must be [0, 1]");
        updateCounters(1); // +1 on creation
    }

    // Custom Rule of 3 to handle counters correctly on copies/destructions
    Item(const Item& other) {
        *this = other; // delegate to assignment operator
    }

    Item& operator=(const Item& other) {
        if (this != &other) {
            updateCounters(-1); // Remove old state from counters
            m_category = other.m_category;
            m_description = other.m_description;
            m_id = other.m_id;
            m_price = other.m_price;
            m_discount = other.m_discount;
            updateCounters(1); // Add new state to counters
        }
        return *this;
    }

    ~Item() {
        updateCounters(-1); // -1 on destruction
    }

    // Accessors
    std::string getId() const { return m_id; }
    ItemType getCategory() const { return m_category; }
    double getDiscount() const { return m_discount; }
    std::string getDescription() const { return m_description; }
    double getPrice() const { return m_price; }

    // Mutator for discount (updates counters automatically)
    void setDiscount(double discount) {
        if (discount < 0.0 || discount > 1.0) throw std::invalid_argument("Discount must be [0, 1]");
        updateCounters(-1); // Remove current state
        m_discount = discount;
        updateCounters(1);  // Add new state
    }

    // Static accessors for the counters
    static int getGamingCount() { return s_gamingCount; }
    static int getDiscountedCount() { return s_discountedCount; }
};

// Initialize static variables
int Item::s_gamingCount = 0;
int Item::s_discountedCount = 0;
---------------------------------------------------------------------

PART 3 : SHOPPINGCART CLASS
--------------------------------------------------------------------

// =======================================================================
// 3. SHOPPING CART CLASS
// =======================================================================
class ShoppingCart {
protected: // Protected so derived class can access them
    Item* m_pItems{};
    size_t m_cnt{};

public:
    ShoppingCart() = default;

    // Rule of 5
    virtual ~ShoppingCart() { delete[] m_pItems; }

    ShoppingCart(const ShoppingCart& other) {
        m_cnt = other.m_cnt;
        m_pItems = new Item[m_cnt];
        for (size_t i = 0; i < m_cnt; ++i) m_pItems[i] = other.m_pItems[i];
    }

    ShoppingCart& operator=(const ShoppingCart& other) {
        if (this != &other) {
            delete[] m_pItems;
            m_cnt = other.m_cnt;
            m_pItems = new Item[m_cnt];
            for (size_t i = 0; i < m_cnt; ++i) m_pItems[i] = other.m_pItems[i];
        }
        return *this;
    }

    ShoppingCart(ShoppingCart&& other) noexcept : m_pItems(other.m_pItems), m_cnt(other.m_cnt) {
        other.m_pItems = nullptr;
        other.m_cnt = 0;
    }

    ShoppingCart& operator=(ShoppingCart&& other) noexcept {
        if (this != &other) {
            delete[] m_pItems;
            m_pItems = other.m_pItems;
            m_cnt = other.m_cnt;
            other.m_pItems = nullptr;
            other.m_cnt = 0;
        }
        return *this;
    }

    // Add items (Virtual so Derived can override)
    virtual void add(const Item& item) {
        Item* temp = new Item[m_cnt + 1];
        for (size_t i = 0; i < m_cnt; ++i) temp[i] = m_pItems[i];
        temp[m_cnt] = item;
        delete[] m_pItems;
        m_pItems = temp;
        m_cnt++;
    }

    // Remove item by ID
    void remove(const std::string& id) {
        removeIf([&](const Item& i) { return i.getId() == id; });
    }

    // Remove by lambda
    void removeIf(std::function<bool(const Item&)> predicate) {
        size_t keepCount = 0;
        for (size_t i = 0; i < m_cnt; ++i) {
            if (!predicate(m_pItems[i])) keepCount++;
        }

        Item* temp = new Item[keepCount];
        for (size_t i = 0, j = 0; i < m_cnt; ++i) {
            if (!predicate(m_pItems[i])) temp[j++] = m_pItems[i];
        }
        delete[] m_pItems;
        m_pItems = temp;
        m_cnt = keepCount;
    }

    // Remove all items from a specified category
    void removeByCategory(ItemType cat) {
        removeIf([=](const Item& i) { return i.getCategory() == cat; });
    }

    // Remove items that don't have a discount
    void removeNoDiscount() {
        removeIf([](const Item& i) { return i.getDiscount() == 0.0; });
    }

    // Update discount for a specific category
    void updateDiscount(ItemType cat, double newDiscount) {
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_pItems[i].getCategory() == cat) {
                m_pItems[i].setDiscount(newDiscount);
            }
        }
    }

    // Print to screen formatted as a table
    void printTable() const {
        std::cout << std::left 
                  << std::setw(15) << "ID" 
                  << std::setw(25) << "Description" 
                  << std::setw(10) << "Price" 
                  << std::setw(10) << "Discount" << "\n";
        std::cout << std::string(60, '-') << "\n";
        
        for (size_t i = 0; i < m_cnt; ++i) {
            std::cout << std::left 
                      << std::setw(15) << m_pItems[i].getId()
                      << std::setw(25) << m_pItems[i].getDescription()
                      << "$" << std::setw(9) << m_pItems[i].getPrice()
                      << (m_pItems[i].getDiscount() * 100) << "%\n";
        }
    }
};

//--------------------------------------------------------------------

//PART 4: DERIVED UNIQUECART CLASS

//-------------------------------------------------------------------

// =======================================================================
// 4. DERIVED CLASS
// =======================================================================
class UniqueCart : public ShoppingCart {
    char* m_name{}; // Resource managed by this class

public:
    UniqueCart(const char* name) {
        if (name) {
            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);
        }
    }

    // Rule of 5 for Derived Class
    ~UniqueCart() override {
        delete[] m_name;
    }

    UniqueCart(const UniqueCart& other) : ShoppingCart(other) {
        if (other.m_name) {
            m_name = new char[strlen(other.m_name) + 1];
            strcpy(m_name, other.m_name);
        }
    }

    UniqueCart& operator=(const UniqueCart& other) {
        if (this != &other) {
            ShoppingCart::operator=(other); // Call base assignment
            delete[] m_name;
            m_name = nullptr;
            if (other.m_name) {
                m_name = new char[strlen(other.m_name) + 1];
                strcpy(m_name, other.m_name);
            }
        }
        return *this;
    }

    UniqueCart(UniqueCart&& other) noexcept : ShoppingCart(std::move(other)), m_name(other.m_name) {
        other.m_name = nullptr;
    }

    UniqueCart& operator=(UniqueCart&& other) noexcept {
        if (this != &other) {
            ShoppingCart::operator=(std::move(other)); // Call base move
            delete[] m_name;
            m_name = other.m_name;
            other.m_name = nullptr;
        }
        return *this;
    }

    // Override add to ensure unique IDs
    void add(const Item& item) override {
        // Check for duplicates
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_pItems[i].getId() == item.getId()) {
                throw std::invalid_argument("Item with this ID already exists in the cart.");
            }
        }
        // If clear, call base class add
        ShoppingCart::add(item);
    }
    
    // Accessor for the cart name
    const char* getName() const { return m_name ? m_name : "Unnamed"; }
};

//-----------------------------------------------------------------------------


