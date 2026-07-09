#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <ostream>
#include <iomanip>

namespace seneca {
  /********************************************************
  * SpellChecker class holds two parallel arrays of string
  * both of size 6
  **********************************************************/
  class SpellChecker
  {
    std::string m_badWords[6]{}; //an array with 6 misspelled words
    std::string m_goodWords[6]{}; //array with the correct spelling of those words
    size_t m_replacements[6]{};
  public:

    /**********************************
    * Receives the address of a C-style
    *  string that holds the file name with 
    * the misspelled words. If the file 
    * exists, constructor loads its 
    * contents. If the file is missing, 
    * this constructor throws an exception
    *  of type const char*, with the message
    *  Bad file name!. Each line in the 
    * file has the format BAD_WORD  GOOD_WORD;
    *  the two fields can be separated by any 
    * number of spaces.
    **********************************/
    SpellChecker(const char* filename);

    //<---------------------------------------------
    //operator that searches text and
    //replaces misspelled words with correct
    //version. Count how many times each mispelled
    //word has been replaced
    //<------------------------------------------------
    void operator()(std::string& text);

    /*******************************************
    * inserts into the parameter how many times
    * each misspelled word has been replaced by
    * the correct word using the current instance...
    * the format of the output is: 
    *    BAD_WORD: CNT replacements<endl>
    * where BAD_WORD is to be printed on a field of size 15
    *********************************************/
    void showStatistics(std::ostream& out) const;
  };

}
#endif