#include "spellCheker.h"

namespace seneca
{
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
    SpellChecker::SpellChecker(const char* filename)
    {
        std::ifstream file(filename);

        if (!file)
        {
            throw "Bad file name!";
        }

        for (size_t i = 0; i < 6 && file; ++i)
        {
            file >> m_badWords[i] >> m_goodWords[i];
            m_replacements[i] = 0;
        }
    }

    //<---------------------------------------------
    //operator that searches text and
    //replaces misspelled words with correct
    //version. Count how many times each mispelled
    //word has been replaced
    //<------------------------------------------------
    void SpellChecker::operator()(std::string& text)
    {
        for (size_t i = 0; i < 6; ++i)
        {
            size_t pos = 0;

            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos)
            {
                text.replace(pos,
                           m_badWords[i].length(),
                           m_goodWords[i]);

                m_replacements[i]++;

                pos += m_goodWords[i].length();

            }
        }
    }

    /*******************************************
    * inserts into the parameter how many times
    * each misspelled word has been replaced by
    * the correct word using the current instance...
    * the format of the output is: 
    *    BAD_WORD: CNT replacements<endl>
    * where BAD_WORD is to be printed on a field of size 15
    *********************************************/
    void SpellChecker::showStatics(std::ostream& out) const
    {
        for (size_t i = 0; i < 6; ++i)
        {
            out << std::right
                   << std::setw(15)
                   << m_badWords[i]
                   << ": "
                   << m_replacements[i]
                   << " replacements\n";
        }

    }


}