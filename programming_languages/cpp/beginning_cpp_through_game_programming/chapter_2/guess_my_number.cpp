#include <iostream>

namespace using std;

int main()
{
  srand(static_cast<unsigned int>(time(0)));
  int secretNumber = rand() % 100 + 1;
  int tries = 0;
  int guess;
  cout << "Guess my number :D\n" << endl;
  
  do {
    cout << "Enter a guess: " << endl;
    cin >> guess;
    ++tries;
    
    if(guess > secretNumber){
      cout << "Too high!" << endl;
    } else if(guess < secretNumber){
      cout << "Too low!" << endl;
    } else {
      cout << "You've done it in " << tries << " :P" << endl;
    }
  } while(guess != secretNumber);
  
  return 0;
}
