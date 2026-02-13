// try g++ -Wall -std=c++11 -g -o out *.cpp

#include <iostream>
#include "GuessGame.h"

using namespace std;
using namespace sibanda;

int main() {
    GuessGame game;
    int userGuess;
    bool found = false;

    cout << "Step 4: Tracking State and 'this' Pointer" << endl;

    while(!found) {
        cout << "Guess #" << (game.getAttempts() + 1) << ":";
        if(!(cin>>userGuess)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        game.checkGuess(userGuess, found);
    }

    cout << "Game OVer! Total attempts:" <<
    game.getAttempts() << endl;
      return 0;
}