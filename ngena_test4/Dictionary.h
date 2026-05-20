#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <iostream>
#include <string>

namespace seneca {

    enum class PartOfSpeech
    {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };

    struct Word
    {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    /***********************************************
    * -> class Dictionary manages dynamically allocated
    * collection of objects of Type Word in the form 
    * of an array.
    * -> at minimum -> store address of array
    ************************************************/
    class Dictionary {
      Word* m_words{ nullptr };
      size_t m_count{ 0 };

      // Helper function to format tags
      std::string formatPOS(PartOfSpeech pos) const;

    public:
      Dictionary(); // = default;
      Dictionary(const char* filename);
      //rule of 5?
      ~Dictionary();
      Dictionary(const Dictionary& src);
      Dictionary& operator=(const Dictionary& src);
      Dictionary(Dictionary&& src) noexcept;
      Dictionary& operator=(Dictionary&& src) noexcept;

      /****************************************************
      * void searchWord(const char* word) - searches in the
      * -> searches in the collection of words the one
      * specified as a parameter. If the word is found,
      * print the definitions in the following format
      *****************************************************/
      void searchWord(const char* word) const;

    

    };

}
#endif
