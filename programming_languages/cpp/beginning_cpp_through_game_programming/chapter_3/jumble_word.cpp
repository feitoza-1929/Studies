#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    enum fields
    {
        WORD,
        HINT,
        NUM_FIELDS
    };
    const int NUM_WORDS = 2;
    const string WORDS[NUM_WORDS][NUM_FIELDS] =
    {
        {"capivara", "animal brasileiro."},
        {"oculos", "sempre os perco na minha cara."}
    };

    srand(static_cast<unsigned int>(time(0)));
    int choice = (rand() % NUM_WORDS);
    string theWord = WORDS[choice][WORD];
    string theHint = WORDS[choice][HINT];

    string jumble = theWord;
    int length = jumble.size();
    for (int i = 0; i < length; i++)
    {
        int index1 = (rand() % length);
        int index2 = (rand() % length);
        char temp = jumble[index1];
        jumble[index1] = jumble[index2];
        jumble[index2] = temp;
    }

    cout << "\t\t\tWelcome to Word Jumble!\n\n";
    cout << "Unscramble the letters to make a word.\n";
    cout << "Enter ’hint’ for a hint.\n";
    cout << "Enter ’quit’ to quit the game.\n\n";
    cout << "The jumble is: " << jumble;

    string guess;
    cout << "\n\nYour guess: ";
    cin >> guess;

    while ((guess != theWord) && (guess != "quit"))
    {
        if(guess == "hint")
        {
            cout << theHint;
        }
        else
        {
            cout << "Sorry, that's not it.";
        }

        cout << "\n\nYour guess: ";
        cin >> guess;
    }

    if(guess == theWord)
    {
        cout << "\nThat's it! You guessed it!\n";
    }

    cout << "\nThank for playing.\n";
    return 0;
}