#include "bucketCollection.hpp"
#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>
#pragma once

const std::string LETTERS_BY_FREQUENCY = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
constexpr int LETTERS = 26;

int indexOf(const std::string& s, const char c);

char mostFrequentLetterInWord(const uint32_t word);

uint32_t wordToNumber(const std::string& word);

template <size_t n>
BucketCollection<std::string, n, LETTERS> sortWordsByMostFrequentLetter(const std::array<std::string, n>& words)
{
    std::array<std::vector<std::string>, LETTERS> buckets;

    for (const std::string& word : words)
    {
        const char mostFrequentLetter = mostFrequentLetterInWord(wordToNumber(word));
        const char position = indexOf(LETTERS_BY_FREQUENCY, mostFrequentLetter);
        buckets[position].push_back(word);
    }

    BucketCollection<std::string, n, LETTERS> result(buckets);
    return result;
}

bool overlappingLetters(const std::string& a, const std::string& b);

inline bool overlappingLettersWithNumbers(const uint32_t a, const uint32_t b);

template <size_t n>
std::array<uint32_t, n> wordsToNumbers(const std::array<std::string, n>& words)
{
    std::array<uint32_t, n> result;

    for (int i = 0; i < n; i++)
    {
        result[i] = wordToNumber(words[i]);
    }

    return result;
}

template <size_t n>
char getBucketLabel(const BucketCollection<std::string, n, 26>& letterBuckets)
{
    return LETTERS_BY_FREQUENCY[letterBuckets.getCurrentBucket()];
}

#include "lib.tpp"
