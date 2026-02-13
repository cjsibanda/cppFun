#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GuessGame.h"

using namespace std;

namespace sibanda {
    GuessGame::GuessGame() : m_guessCount(0) { // Initialize count to 0
        m_secretNumber = new int;
        srand(static_cast<unsigned int>(time(nullptr)));
        *m_secretNumber = (rand() % 100) + 1;
    }

    GuessGame::~GuessGame() {
        delete m_secretNumber;
        m_secretNumber = nullptr;
    }

    int GuessGame::getAttempts() const {
        return m_guessCount;
    }

    bool GuessGame::isValid(int guess) const {
        return (guess >= 1 && guess <= 100);
    }

    bool GuessGame::checkGuess(int guess) {
        bool correct = false;
        
        this->checkGuess(guess, correct);
        return correct;
    }

    void GuessGame::checkGuess(int guess, bool& isCorrect) {
        
        m_guessCount++;

        if (!isValid(guess)) {
            cout << "Out of range! (1-100)" << endl;
            isCorrect = false;
        }
        
        else if (guess < *(this->m_secretNumber)) {
            cout << "Too low" << endl;
            isCorrect = false;
        } else if (guess > *(this->m_secretNumber)) {
            cout << "Too high" << endl;
            isCorrect = false;
        } else {
            cout << "Correct!" << endl;
            isCorrect = true;
        }
    }
}
