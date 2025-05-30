#include "lib.cpp"
#include <cassert>

int main()
{
   assert(overlappingLetters("APPLE", "PEARS") == true);
   assert(overlappingLetters("APPLE", "BINGO") == false);

   assert(wordToNumber("APPLE") == 0b00000000000000001000100000010001);
   
   std::cout << "All tests passed ^-^\n";
   return 0;
}
