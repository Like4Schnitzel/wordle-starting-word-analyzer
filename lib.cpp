#include <cstdint>
#include <iostream>
#include <string.h>

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

bool overlappingLettersWithNumbers(const uint32_t a, const uint32_t b)
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

template<size_t n>
std::array<uint32_t, n> wordsToNumbers(const std::array<std::string, n>& words)
{
    std::array<uint32_t, n> result;

    for (int i = 0; i < n; i++)
    {
        result[i] = wordToNumber(words[i]);
    }

    return result;
}
