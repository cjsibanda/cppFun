#include "RugbyTeam.h"

//standard library header
#include <iostream>

// remeber using namespace should only apear in cpp files
// should not apear in header/.h files
using namespace std;

//this is a GLOBAL varaible definition
// Memory is allocated HERE
//the g_teamRanking varaible exists for entire duration of program
// it is stored in DATA segment
int g_teamRanking = 1;



    // static member variable definition
    // it must be defined ONCE in a cpp file.
    int RugbyTeam::s_teamObjectsCreated = 0;

    
    // this is an internal global fucntion
    // Internal linkage:
    // only this file can use it.
    // the linker hides this symbol from other modules.
    static void secretTeamMessage() {
        cout << "\n[Rassie's Team Strategy Loaded]\n";
    }

    
    // The Constructor
    RugbyTeam::RugbyTeam()
        : m_teamName("Unknown Team"),
          m_playerCount(0),
          m_totalPoints(0)
    {
        s_teamObjectsCreated++;

        secretTeamMessage();
    }

    
    // Set team name
    void RugbyTeam::setTeamName(const string& name) {

        // some encapsulation:
        // modifyies a private variable through public function
        m_teamName = name;
    }

    
    // Adding player into the array
    void RugbyTeam::addPlayer(const string& playerName) {

        // to prevent array overflow
        if (m_playerCount < MAX_PLAYERS) {

            m_players[m_playerCount] = playerName;

            m_playerCount++;
        }
        else {

            cout << "Sorry.. the team is already full.\n";
        }
    }

    
    // Rugby scoring -> a try is 5 points
    void RugbyTeam::scoreTry() {

        m_totalPoints += 5;
    }

    
    // Displaying all team data
    void RugbyTeam::displayTeam() const {

        cout << "\n>>>>>>>>>>>>>>>>>>>>>>>\n";
        cout << "SPRINGBOKS TEAM INFO\n";
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<\n";

        cout << "Team Name: " << m_teamName << endl;

        cout << "World Rugby Ranking: "
             << g_teamRanking << endl;

        cout << "Total Points: "
             << m_totalPoints << endl;

        cout << "\nPlayers:\n";

        // Range-based loop (from C++11+)
        for (int i = 0; i < m_playerCount; i++) {

            cout << "- " << m_players[i] << endl;
        }

        cout << "=============================\n";
    }

    // ---------------------------------------------------------
    // Reading bok players from text file
    // ---------------------------------------------------------
    void RugbyTeam::loadPlayersFromFile(
        const string& filename)
    {
        ifstream file(filename);

        // Check if file opened correctly
        if (!file) {

            cout << "Soory but the filec could not open file.\n";

            return;
        }

        string playerName;

        // Read each line from file
        while (getline(file, playerName)) {

            addPlayer(playerName);
        }

        file.close();
    }

    
    // Static member function
    int RugbyTeam::getObjectCount() {

        return s_teamObjectsCreated;
    }

} // namespace rugby
