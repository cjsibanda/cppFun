#ifndef SIBANDA_GUESSGAME_H_
#define SIBANDA_GUESSGAME_H_

namespace sibanda {
    class GuessGame {
        int* m_secretNumber;
        int m_guessCount; // Private counter to track attempts

        bool isValid(int guess) const;

    public:
        GuessGame();
        ~GuessGame();

        // Overloaded methods to check guesses
        bool checkGuess(int guess);
        void checkGuess(int guess, bool& isCorrect);

        // Public getter for the counter (Read-only)
        int getAttempts() const;
    };
}

#endif
