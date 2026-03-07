#ifndef SPRINGBOKS_PLAYER_H_
#define SPRINGBOKS_PLAYER_H_
#include <iostream>
namespace springboks {
    //Base class
    class RugbyPlayer {
        //private is assumed for class
    private:
      long playerNumber{};
      char playerFirstName[41]{};
      char playerLastName[41]{};
    public:
      //constructors
      RugbyPlayer();
      RugbyPlayer(long);
      RugbyPlayer(long, const char*, const char*);
      //Setter/mutator function
      RugbyPlayer& read(std::istream&);
    // THE protected access modifier
    // limits access to members of a derived class
    protected:
       const RugbyPlayer& print(std::ostream&) const;
    };

    //Helper functions
    std::istream& operator>>(std::ostream&, RugbyPlayer&);

    //THE derived class
    //can add member variables and member functions to derived class
    class MinutesLimitedlayer : public RugbyPlayer {
     private:
       //specific data members
       double minutesPlayed{};
       double heartRate{};
     public:
       //Derived class getters
       double getMinutesPlayed() const;
       double getHeartRate() const;
       //Dervived class setters
       MinutesLimitedlayer& setMinutesPlayed(double);
       MinutesLimitedlayer& setHeartRate(double);

       //THE print function for the derived class
       //granting protected access
       const MinutesLimitedlayer& print(std::ostream&) const;
    };
}
#endif //!SPRINGBOKS_PLAYER