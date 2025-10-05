#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

class NumberGuessingGame {
private:
    int secretNumber;
    int attempts;
    int maxAttempts;
    int minRange;
    int maxRange;

public:
    NumberGuessingGame(int min = 1, int max = 100, int maxTries = 10) {
        minRange = min;
        maxRange = max;
        maxAttempts = maxTries;
        attempts = 0;
        
        // Seed the random number generator
        srand(time(0));
        secretNumber = rand() % (maxRange - minRange + 1) + minRange;
    }

    void displayWelcomeMessage() {
        cout << "=== Welcome to the Number Guessing Game! ===" << endl;
        cout << "I'm thinking of a number between " << minRange << " and " << maxRange << endl;
        cout << "Can you guess it in " << maxAttempts << " attempts or less?" << endl;
        cout << "Let's begin!\n" << endl;
    }

    void displayGameStats() {
        cout << "\n--- Game Statistics ---" << endl;
        cout << "Secret number: " << secretNumber << endl;
        cout << "Your attempts: " << attempts << endl;
        cout << "Max attempts: " << maxAttempts << endl;
    }

    void playGame() {
        int guess;
        bool hasWon = false;

        displayWelcomeMessage();

        while (attempts < maxAttempts) {
            cout << "Attempt " << (attempts + 1) << "/" << maxAttempts << endl;
            cout << "Enter your guess: ";
            
            // Input validation
            if (!(cin >> guess)) {
                cout << "Invalid input! Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            attempts++;

            if (guess == secretNumber) {
                hasWon = true;
                break;
            } else if (guess < secretNumber) {
                cout << "Too low! ";
                
                // Provide additional hints
                if (secretNumber - guess > 20) {
                    cout << "You're way too low!" << endl;
                } else if (secretNumber - guess > 10) {
                    cout << "Try a bit higher!" << endl;
                } else {
                    cout << "You're very close, just a little higher!" << endl;
                }
            } else {
                cout << "Too high! ";
                
                // Provide additional hints
                if (guess - secretNumber > 20) {
                    cout << "You're way too high!" << endl;
                } else if (guess - secretNumber > 10) {
                    cout << "Try a bit lower!" << endl;
                } else {
                    cout << "You're very close, just a little lower!" << endl;
                }
            }

            // Show remaining attempts
            int remaining = maxAttempts - attempts;
            if (remaining > 0) {
                cout << "You have " << remaining << " attempt(s) remaining.\n" << endl;
            }
        }

        displayResult(hasWon);
        
        if (!hasWon) {
            displayGameStats();
        }
    }

    void displayResult(bool hasWon) {
        cout << "\n=== GAME OVER ===" << endl;
        if (hasWon) {
            cout << "🎉 Congratulations! You guessed the number!" << endl;
            cout << "It took you " << attempts << " attempt(s) to find " << secretNumber << endl;
            
            // Performance rating
            if (attempts <= 3) {
                cout << "⭐ Excellent! You're a guessing master!" << endl;
            } else if (attempts <= 6) {
                cout << "👍 Great job! You're pretty good at this!" << endl;
            } else {
                cout << "😊 Well done! You got it!" << endl;
            }
        } else {
            cout << "💔 Sorry! You've used all your attempts." << endl;
            cout << "Better luck next time!" << endl;
        }
    }

    void playAgain() {
        char choice;
        cout << "\nWould you like to play again? (y/n): ";
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            // Reset game
            attempts = 0;
            secretNumber = rand() % (maxRange - minRange + 1) + minRange;
            cout << "\n" << string(50, '-') << endl;
            playGame();
            playAgain();
        } else {
            cout << "\nThank you for playing! Goodbye! 👋" << endl;
        }
    }
};

int main() {
    cout << "🎮 Number Guessing Game" << endl;
    cout << "Developed by: skillCraft Technology\n" << endl;

    // Customizable game settings
    int minNum, maxNum, maxTries;
    
    cout << "Customize your game (or press Enter for defaults):" << endl;
    cout << "Minimum number (default 1): ";
    if (cin.peek() == '\n') {
        minNum = 1;
        cin.ignore();
    } else {
        cin >> minNum;
    }
    
    cout << "Maximum number (default 100): ";
    if (cin.peek() == '\n') {
        maxNum = 100;
        cin.ignore();
    } else {
        cin >> maxNum;
    }
    
    cout << "Maximum attempts (default 10): ";
    if (cin.peek() == '\n') {
        maxTries = 10;
        cin.ignore();
    } else {
        cin >> maxTries;
    }

    // Input validation for range
    if (minNum >= maxNum) {
        cout << "Invalid range! Using default values (1-100)." << endl;
        minNum = 1;
        maxNum = 100;
    }
    
    if (maxTries <= 0) {
        cout << "Invalid attempts! Using default (10)." << endl;
        maxTries = 10;
    }

    // Create and start the game
    NumberGuessingGame game(minNum, maxNum, maxTries);
    game.playGame();
    game.playAgain();

    return 0;
}