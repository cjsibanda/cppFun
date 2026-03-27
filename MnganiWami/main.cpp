#include <iostream>
#include "Liverpool.h"

using namespace sibanda;

int main() {
    //Standard Player (Static Memory)
    Player captain(10, "Steven", "Gerrard");
    
    //Loaned Player (DMA)
    int loanSpells[] = {6, 12, 5};
    LoanedPlayer youngster(5, "Xavi", "Alonso", 3, loanSpells);

    std::cout << "Diplaying Players:" << std::endl;
    captain.display();
    std::cout << std::endl;
    youngster.display();

    //Testing Deep Copy
    LoanedPlayer copyPlayer = youngster;
    std::cout << "Displaying Copy:" << std::endl;
    copyPlayer.display();

    return 0;

}
