#ifndef SIBANDA_LIVERPOOL_H_
#define SIBANDA_LIVERPOOL_H_

namespace sibanda {
    //Base class representing Liverpool player
    class Player {
    private:
      long m_kitNumber{};
      char m_fName[41]{};
      char m_lName[41]{};
    public:
      Player();
      Player(long kitNum, const char* fName, const char* lName);

      //Query to display basic player info
      const Player& display() const;

      // Virtual destructor make sure proper cleanup of derived classes
      virtual ~Player() = default;

    };

    //Derived class for players sent out on multiple loans
    class LoanedPlayer : public Player {
    private:
      int m_noOfLoans{};
      //Pointer to hold array of months for loan spell
      int* m_loanMonths{};
    public:
      LoanedPlayer();
      LoanedPlayer(long kitNum, const char* fName, const char* lName, int numLoans, int* months);
      
      //Overridden display
      const LoanedPlayer& display() const;

      //The Rule of Three (Required due to DMA)
      LoanedPlayer(const LoanedPlayer& source);  //Copy Constructor
      LoanedPlayer& operator=(const LoanedPlayer& source); //Copy Assignment Operator
      ~LoanedPlayer(); //destructor
    };
}

#endif