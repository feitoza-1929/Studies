#include <stdlib.h>
#include <iostream>

using namespace std;

enum DifficultLevel{
  EASY = 1,
  MEDIUM = 2,
  HARD = 3
};

int main()
{
  cout << "SELECT THE DIFFICULT LEVEL\n" << endl;
  cout << "1 - EASY\n2 - MEDIUM\n3 - HARD" << endl;

  unsigned int level;
  cin >> level;
  
  switch (level){
  case DifficultLevel::EASY:
    cout << "You choose easy mode" << endl;
    break;
  case DifficultLevel::MEDIUM:
    cout << "You choose medium mode" << endl;
    break;
  case DifficultLevel::HARD:
    cout << "This is the way!" << endl;
    break;
  };
  return 0;
}
