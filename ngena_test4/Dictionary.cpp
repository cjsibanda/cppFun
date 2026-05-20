#include <fstream>
#include <sstream>
#include <utility>
#include "Dictionary.h"
#include "Settings.h"

namespace seneca {

    // Helper to translate part of speech token to text representation
    std::string Dictionary::formatPOS(PartOfSpeech pos) const {
        switch (pos) {
            case PartOfSpeech::Noun:         return "noun";
            case PartOfSpeech::Pronoun:      return "pronoun";
            case PartOfSpeech::Adjective:    return "adjective";
            case PartOfSpeech::Adverb:       return "adverb";
            case PartOfSpeech::Verb:         return "verb";
            case PartOfSpeech::Preposition:  return "preposition";
            case PartOfSpeech::Conjunction:  return "conjunction";
            case PartOfSpeech::Interjection: return "interjection";
            default:                         return "";
        }
    }

    Dictionary::Dictionary(const char* filename) {
        if (!filename || filename[0] == '\0') return;

        std::ifstream file(filename);
        if (!file.is_open()) return;

        //  Count rows to allocate precise storage limits
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) m_count++;
        }

        if (m_count == 0) return;

        // Allocate exact memory block required
        m_words = new Word[m_count];

        // Reset stream to read and parse CSV data elements
        file.clear();
        file.seekg(0, std::ios::beg);

        size_t index = 0;
        while (std::getline(file, line) && index < m_count) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string word, pos_str, def;

            // Split line by commas safely: word,pos,definition
            if (std::getline(ss, word, ',') && 
                std::getline(ss, pos_str, ',') && 
                std::getline(ss, def)) {
                
                m_words[index].m_word = word;
                m_words[index].m_definition = def;

                // Resolve matching PartOfSpeech enum values
                if (pos_str == "n." || pos_str == "n. pl.") m_words[index].m_pos = PartOfSpeech::Noun;
                else if (pos_str == "adv.") m_words[index].m_pos = PartOfSpeech::Adverb;
                else if (pos_str == "a.") m_words[index].m_pos = PartOfSpeech::Adjective;
                else if (pos_str == "v." || pos_str == "v. i." || pos_str == "v. t." || pos_str == "v. t. & i.") m_words[index].m_pos = PartOfSpeech::Verb;
                else if (pos_str == "prep.") m_words[index].m_pos = PartOfSpeech::Preposition;
                else if (pos_str == "pron.") m_words[index].m_pos = PartOfSpeech::Pronoun;
                else if (pos_str == "conj.") m_words[index].m_pos = PartOfSpeech::Conjunction;
                else if (pos_str == "interj.") m_words[index].m_pos = PartOfSpeech::Interjection;
                else m_words[index].m_pos = PartOfSpeech::Unknown;

                index++;
            }
        }
    }

    // Destructor
    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    // Copy Constructor
    Dictionary::Dictionary(const Dictionary& src) {
        *this = src;
    }

    // Copy Assignment Operator
    Dictionary& Dictionary::operator=(const Dictionary& src) {
        if (this != &src) {
            delete[] m_words;
            m_count = src.m_count;
            if (src.m_words) {
                m_words = new Word[m_count];
                for (size_t i = 0; i < m_count; ++i) {
                    m_words[i] = src.m_words[i];
                }
            } else {
                m_words = nullptr;
            }
        }
        return *this;
    }

    // Move Constructor
    Dictionary::Dictionary(Dictionary&& src) noexcept {
        *this = std::move(src);
    }

    // Move Assignment Operator
    Dictionary& Dictionary::operator=(Dictionary&& src) noexcept {
        if (this != &src) {
            delete[] m_words;
            m_words = src.m_words;
            m_count = src.m_count;

            src.m_words = nullptr;
            src.m_count = 0;
        }
        return *this;
    }

    void Dictionary::searchWord(const char* word) const {
        if (!word || word[0] == '\0') return;

        bool found = false;
        bool isFirstMatch = true;
        std::string target(word);

        for (size_t i = 0; i < m_count; ++i) {
            if (m_words[i].m_word == target) {
                found = true;

                //--> to handle conditional visibility flags
                bool printPOS = g_settings.m_verbose && (m_words[i].m_pos != PartOfSpeech::Unknown);
                std::string posLabel = printPOS ? "(" + formatPOS(m_words[i].m_pos) + ") " : "";

                if (isFirstMatch) {
                    std::cout << m_words[i].m_word << " - " << posLabel << m_words[i].m_definition << "\n";
                    isFirstMatch = false;
                } else {
                    // Indent subsequent matches by matching word string lengths
                    std::string spaces(m_words[i].m_word.length(), ' ');
                    std::cout << spaces << " - " << posLabel << m_words[i].m_definition << "\n";
                }

                // If configuration states show_all is false, break on the first find
                if (!g_settings.m_show_all) {
                    return;
                }
            }
        }

        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary.\n";
        }
    }
}