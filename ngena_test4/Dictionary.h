#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <iostream>
#include <string>

//do I need this??...
//All cllases inside seneca?
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
      std::string* word[]; //??????? placeholder(check!)
    public:
      Dictionary();
      Dictionary(const char* filename);
      //No rule of 3?

      /****************************************************
      * void searchWord(const char* word) - searches in the
      * -> searches in the collection of words the one
      * specified as a parameter. If the word is found,
      * print the definitions in the following format
      *****************************************************/


    

    }

}

