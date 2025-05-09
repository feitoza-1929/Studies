#include <iostream>

using std::cout;
using std::endl;

int main()
{
    cout << "counting foward ";
    for (int i = 0; i < 10; i++)
    {
        cout << i << " ";
    }
    cout << "\n" << endl;

    int count = 10;
    cout << "counting backwards ";
    for (;;)
    {
        if(count < 1)
            break;
        cout << --count << " ";
    }
    cout << "\n" << endl;

    return 0;
}
