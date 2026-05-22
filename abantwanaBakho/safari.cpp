#include "safari.h"
using namespace std;

// Constructor
Safari::Safari() : m_places(nullptr), m_size(0) {}

// Copy constructor (deep copy)
Safari::Safari(const Safari& other) {
    m_size = other.m_size;
    m_places = new string[m_size];

    for (int i = 0; i < m_size; ++i)
        m_places[i] = other.m_places[i];
}

// Move constructor (stealing resources!)
Safari::Safari(Safari&& other) noexcept {
    m_places = other.m_places;
    m_size = other.m_size;

    other.m_places = nullptr;
    other.m_size = 0;
}

// Copy assignment
Safari& Safari::operator=(const Safari& other) {
    if (this != &other) {
        delete[] m_places;

        m_size = other.m_size;
        m_places = new string[m_size];

        for (int i = 0; i < m_size; ++i)
            m_places[i] = other.m_places[i];
    }
    return *this;
}

// Move assignment
Safari& Safari::operator=(Safari&& other) noexcept {
    if (this != &other) {
        delete[] m_places;

        m_places = other.m_places;
        m_size = other.m_size;

        other.m_places = nullptr;
        other.m_size = 0;
    }
    return *this;
}

// Destructor
Safari::~Safari() {
    delete[] m_places;
}

// Adding place
void Safari::addPlace(const string& place) {
    string* temp = new string[m_size + 1];

    for (int i = 0; i < m_size; ++i)
        temp[i] = m_places[i];

    temp[m_size] = place;

    delete[] m_places;
    m_places = temp;
    ++m_size;
}

// Print destinations
void Safari::print() const {
    cout << "Safari Route:\n";
    for (int i = 0; i < m_size; ++i)
        cout << " - " << m_places[i] << "\n";
}