#include <cstdint>
#include <iostream>
#include <string.h>
#pragma once

const std::string LETTERS_BY_FREQUENCY = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

char mostFrequentLetterInWord(const uint32_t word);

bool overlappingLetters(const std::string& a, const std::string& b);

bool overlappingLettersWithNumbers(const uint32_t a, const uint32_t b);

uint32_t wordToNumber(const std::string& word);
