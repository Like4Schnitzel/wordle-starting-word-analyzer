#include "lib.cpp"
#include <cassert>

int main()
{
   assert(overlappingLetters("APPLE", "PEARS") == true);
   assert(overlappingLetters("APPLE", "BINGO") == false);

   assert(wordToNumber("APPLE") == 0b00000000000000001000100000010001);

   assert(overlappingLettersWithNumbers(wordToNumber("APPLE"), wordToNumber("PEARS")) == true);
   assert(overlappingLettersWithNumbers(wordToNumber("APPLE"), wordToNumber("BINGO")) == false);

   assert(mostFrequentLetterInWord(wordToNumber("APPLE")) == 'E');
   assert(mostFrequentLetterInWord(wordToNumber("BOBBY")) == 'O');
   
   std::cout << "All tests passed ^-^\n";
   return 0;
}
