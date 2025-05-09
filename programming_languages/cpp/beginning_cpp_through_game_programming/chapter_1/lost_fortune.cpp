#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
  string adventurerName;
  int partySize;
  int drinkedBeers;
  
  cout << "\nWelcome to a Simple Adventure\n" << endl;
  cout << "\nPlease enter some piece of information to personalize your adventure" << endl;
  
  cout << "\nWhat's your name adventurer?" << endl;
  cin >> adventurerName;
  
  cout << "\nEnter a number: " << endl;
  cin >> partySize;
  
  cout <<"\nEnter a number smaller than the first: " << endl;
  cin >> drinkedBeers;

  cout << "\nA group of " << partySize << " brave adventurers were in a tavern looking for information about a mysterious place, that was five hours and "<< drinkedBeers * partySize <<" beers ago." << endl;
  cout << "\nBut our great leader " << adventurerName  << " is... asleep !? *that's real?*" << endl;
}
