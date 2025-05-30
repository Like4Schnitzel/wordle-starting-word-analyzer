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
