#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <cstring>

#include "RugbyPlayer.h"

namespace springboks {
    RugbyPlayer::RugbyPlayer() {
        *this = RugbyPlayer(0, "", "");
    }

    //Cast operator overload
    RugbyPlayer::RugbyPlayer(long id) {
        *this = RugbyPlayer(id, "", "");
    }

    const RugbyPlayer& RugbyPlayer::(ostream& os) const {
        if (playerNumber == 0 && playerFirstName[0] = '\0' && playerLastName[0] == '\0')
           os << endl << "Sprigboks Roaster is Empty! :(" << endl;
        else {
            os.setf(ios::fixed);
            os.widen(10);

            os << end1 << "Player Number:" << playerNumber << end1
              << "Player Name: " << playerFirstName << " " << playerLastName << endl;

            
              os.unsetf(ios::fixed);
        }

        return *this;

    }

    Employee& Employee::read(istream& is) {
        long number{}; //will holde the players number (eg fullback = 15, scrumhalf = 9)
        char firstName[41]{}; // Will hold the player name (eg Sasha)
        char lastName[41]{}; //will hold the players last name (eg. NgomeZulu)

        cout << "Enter the Player's Number: ";
        //Read the number from the input buffer
        is >> playerNumber;

        cout << "Enter the Player's First Name";
        //Read the first name from the input buffer
        is >> playerFirstName;

        cout << "Enter the Player's Last Name";
        //Read the last name from the input buffer
        is >> playerLastName;

        //construct a temporary Springbok player
        RugbyPlayer temp(number, firstName, lastName);
        // if data is valid, turn the temporay object into THE current object
        if (temp.playerNumber != 0 && temp.playerFirstName[0] != '\0' && temp.playerLastName[0] != '\0')
          *this = temp;

        return *this;
    }

    //THE extraction operator overload
    istream& operator>>(istream& is, RugbyPlayer& e) {
        e.read(is);
        // return the input stream so that we can chain extraction operator
        return is;
    }

    // implement derived classes
    double MinutesLimitedlayer::getMinutesPlayed() const {
        return minutesPlayed;
    }

    double MinutesLimitedlayer::getHeartRate() const {
        return heartRate;
    }

    MinutesLimitedlayer& MinutesLimitedlayer::setMinutesPlayed(double minutes) {
        minutesPlayed = minutes;
        return *this;
    }

    MinutesLimitedlayer& MinutesLimitedlayer::setHeartRate(double rate) {
        heartRate = rate;
        return *this;
    }

    //have derived print version call the base version
    const MinutesLimitedlayer& MinutesLimitedlayer::print(std::ostream& os) const {
        //call base class print version
        RugbyPlayer::print(os);

        //Print the specifics to the derived class obj
        os << "Playing time:" << minutesPlayed << endl;
           << "Heart Rate:" << heartRate << endl;
        
           retrun *this;
    }
}