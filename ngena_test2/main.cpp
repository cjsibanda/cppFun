#include <iostream>

// Include custom header AFTER standard headers
#include "RugbyTeam.h"

using namespace std;


// main()
// Entry point of program
// argc = argument count
// argv = argument vector
int main(int argc, char** argv)
{
    // Stack variable
    // it exists only during main()
    // it is stored in stack memory
    rugby::RugbyTeam springboks;


    // Accessing global variable from another module
    // this shows external linkage
    
    rugby::g_teamRanking = 1;

    springboks.setTeamName("SA Springboks");

    
    // Load player names from text file
    springboks.loadPlayersFromFile("players.txt");

    // to similate try scoring
    springboks.scoreTry();
    springboks.scoreTry();

    // displaying team information
    springboks.displayTeam();

    
    // a static member function
    cout << "\nObjects Created: "
         << rugby::RugbyTeam::getObjectCount()
         << endl;

    
    // this is a const variable
    // its value alue cannot change after initialization
    const int worldCupsWon = 4;

    cout << "World Cups Won: "
         << worldCupsWon << endl;

    
    // a constexpr variable
    // It must be known at compile time
    constexpr int playersOnField = 15;

    cout << "Players on Field: "
         << playersOnField << endl;

    // Example of a local static variable
    // it exists through entire program lifetime
    static int timesProgramRun = 1;

    cout << "Program Run Count: "
         << timesProgramRun << endl;

    return 0;
}