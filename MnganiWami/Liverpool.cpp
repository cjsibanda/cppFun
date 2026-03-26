#include <iostream>
#include <cstring>
#include "Liverpool.h"

using namespace std;

namespace sibanda {
    // Player Implementation
    Player::Player() {}

    Player::Player(long kitNum, const char* fName, const char* lName) : m_kitNumber(kitNum) {
        if (fName && lName) {
            strncpy(m_fName, fName, 40);
            strncpy(m_lName, lName, 40);
        }
    }

    const Player& Player::display() const {
        cout << "Kit #" << m_kitNumber << ": " << m_fName << " " << m_lName;
        return *this;
    }

    //  LoanedPlayer Implementation
    LoanedPlayer::LoanedPlayer() : Player() {}

    LoanedPlayer::LoanedPlayer(long kit, const char* f, const char* l, int n, int* m) 
        : Player(kit, f, l), m_noOfLoans(n) {
        if (n > 0 && m != nullptr) {
            m_loanMonths = new int[m_noOfLoans];
            for (int i = 0; i < m_noOfLoans; i++) {
                m_loanMonths[i] = m[i];
            }
        }
    }

    // Destructor: Clean up dynamic array
    LoanedPlayer::~LoanedPlayer() {
        delete[] m_loanMonths;
    }

    // Copy Constructor
    LoanedPlayer::LoanedPlayer(const LoanedPlayer& src) : Player(src) {
        m_noOfLoans = src.m_noOfLoans;
        if (src.m_loanMonths) {
            m_loanMonths = new int[m_noOfLoans];
            for (int i = 0; i < m_noOfLoans; i++) m_loanMonths[i] = src.m_loanMonths[i];
        }
    }

    // Copy Assignment
    LoanedPlayer& LoanedPlayer::operator=(const LoanedPlayer& src) {
        if (this != &src) {
            // 1. Base class assignment
            Player::operator=(src);
            // 2. Cleanup current memory
            delete[] m_loanMonths;
            // 3. Copy new data
            m_noOfLoans = src.m_noOfLoans;
            if (src.m_loanMonths) {
                m_loanMonths = new int[m_noOfLoans];
                for (int i = 0; i < m_noOfLoans; i++) m_loanMonths[i] = src.m_loanMonths[i];
            } else {
                m_loanMonths = nullptr;
            }
        }
        return *this;
    }

    const LoanedPlayer& LoanedPlayer::display() const {
        Player::display();
        if (m_noOfLoans > 0) {
            cout << " | Loans: ";
            for (int i = 0; i < m_noOfLoans; i++) cout << m_loanMonths[i] << "m ";
        }
        cout << endl;
        return *this;
    }
}