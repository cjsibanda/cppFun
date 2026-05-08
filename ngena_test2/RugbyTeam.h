//practice run
#ifndef RUGBYTEAM_H
#define RUGBYTEAM_H

//-> standard headers FIRST
#include <string>
#include <fstream>

////////////////////////////////////////////////////////
// -> the namespace prevents conflicts/issues with
// .. other code
// -> everything in this namespace is from rugby module
////////////////////////////////////////////////////////

namespace rugby {
    // constexpt is a compile-time constant
    //-> the compiler MUST know the vakue during compilation
    constexpr int MAX_PLAYERS = 15;

    // extern declaration
    // it does NOT create memory
    // it only tells other files:
    //
    // -> it says ...
    // "There is a variable called g_teamRanking that exists somewhere"
    extern int g_teamRanking;
    
    /*
    -> the RubgyTeam class
    -> private/public access
    */
    class RugbyTeam {
    private:  
      std::string m_teamName;

      //Fixed-size array
      //Size MUST be known at compile time
      std::string m_players[MAX_PLAYERS];

      int m_playerCount;

      int m_totalPoints;

      // a static class varaible
      // shared across ALL objects
      // only ONE copy exists in memory
      static int s_teamObjectsCreated;

    public:
       //Constructor
       RugbyTeam();

       //Member function declarations
       void setTeamName(const std::string& name);

       void addPlayer(const std::string& playerName);

       void scoreTry();

       void displayTeam() const;

       void loadPlayersFromFile(const std::string& filename);

       //a static member function
       static int getObjectCount();
    };
} //namespace rugby

#endif