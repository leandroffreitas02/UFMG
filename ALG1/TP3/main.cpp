#include "loja.hpp"
#include <iostream>

int main()
{

  int TestCases;
  std::cin >> TestCases;

  while(TestCases--){

    int Rolls;
    std::cin >> Rolls;

    Store s(Rolls);
    s.ReadValues();

    std::cout << s.MaxLengthShelf() << std::endl;
  }
}