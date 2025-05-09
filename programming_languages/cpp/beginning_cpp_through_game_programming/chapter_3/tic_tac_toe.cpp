#include <iostream>

using namespace std;

int main()
{
    const int ROWS = 3;
    const int COLUMNS = 3;
    char board[ROWS][COLUMNS] = {{'x', 'x', 'o'}, {'o', 'x', 'o'}, {' ', 'o', 'o'}};

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Is 'X' turn\n" << endl;
    board[2][0] = 'x';
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "The winner is 'X'\n" << endl;

    return 0;
}