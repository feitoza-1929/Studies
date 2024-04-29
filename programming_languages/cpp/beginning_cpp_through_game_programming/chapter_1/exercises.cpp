#include <iostream>
#include <stdlib.h>

int main()
{
  // 1 - list of six variables names (3 bad and 3 good)
  // int 0int;
  // string AVE;
  // const int integer = 0;

  // int integer = 1;
  // string text = "any";
  // const int MAX_LIFE = 3;

  // 2 - explain the result of
  // cout << "Seven divided by three is " << 7 / 3 << endl;
  // cout << "Seven divided by three is " << 7.0 / 3 << endl;
  // cout << "Seven divided by three is " << 7.0 / 3.0 << endl;

  // is getting result of the mathematic expression and concatenating
  // this with the string

  // 3 - gets three game scores from user and display the average
  int scores[3];

  std::cout << "type three game scores: " << std::endl;
  std::cin >> scores[0];
  std::cin >> scores[1];
  std::cin >> scores[2];

  std::cout << "the average score is " << (float)(scores[0] + scores[1] + scores[2])/3.0 << std::endl;
  return 0;
}
