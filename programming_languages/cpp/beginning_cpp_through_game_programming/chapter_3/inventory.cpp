#include <iostream>
#include <string>

using namespace std;

int main()
{
    const int MAX_ITEMS = 10;
    string inventory[MAX_ITEMS];

    int numItems = 0;
    inventory[numItems++] = "sword";
    inventory[numItems++] = "shield";
    inventory[numItems++] = "heal potion";

    cout << "your items:\n" << endl;
    for (int i = 0; i < numItems; i++)
    {
        cout << inventory[i] << endl;
    }

    cout << "\nyou gonna trade your sword for a battle axe\n" << endl;
    inventory[0] = "battle axe";
    numItems++;

    cout << "your items:\n" << endl;
    for (int i = 0; i < numItems; i++)
    {
        cout << inventory[i] << endl;
    }
}