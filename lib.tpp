#include "lib.hpp"

int indexOf(const std::string& s, const char c)
{
    for (int i = 0; i < s.length(); i++) if (s[i] == c) return i;
    return -1;
}

char mostFrequentLetterInWord(const uint32_t word)
{
    for (const auto letter : LETTERS_BY_FREQUENCY)
    {
        if (overlappingLettersWithNumbers(1 << (letter - 'A'), word))
        {
            return letter;
        }
    }

    throw std::invalid_argument("There should be only capital english letters in the word.");
}

bool overlappingLetters(const std::string& a, const std::string& b)
{
    for (auto letterA : a)
    {
        for (auto letterB : b)
        {
            if (letterB == letterA)
            {
                return true;
            }
        }
    }

    return false;
}

inline bool overlappingLettersWithNumbers(const uint32_t a, const uint32_t b)
{
    return a & b;
}

uint32_t wordToNumber(const std::string& word)
{
    uint32_t result = 0;

    for (const auto& letter : word)
    {
        const int alphabetPosition = letter - 'A';
        result |= 1 << alphabetPosition;
    }

    return result;
}
