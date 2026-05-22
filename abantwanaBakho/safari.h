//check
//rule of 5 review
#ifndef SAFARI_H
#define SAFARI_H

#include <iostream>
#include <string>

class Safari {
    std::string* m_places;
    int m_size;
public:
    Safari();       //constructor
    Safari(const Safari& other); //copy constructor
    Safari(safari&& other) noexcept; //move constructor

    Safari& operator=(const Safari& other); //copy assignmnet operator
    Safari& operator=(Safari&& other) noexcept; //move assignment operator

    ~Safari();

    void addPlace(const std::string& place);
    void print() const;
};

#endif