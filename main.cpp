#include "words.hpp"
#include "lib.hpp"
#include "bucketCollection.hpp"
#include <string.h>
#include <algorithm>
#include <ranges>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    constexpr int wordAmount = words.size();

    constexpr int threadCount = 16;
    constexpr int divisibleWordAmount = (1 + wordAmount / threadCount) * threadCount;
    constexpr int wordsPerThread = divisibleWordAmount / threadCount;
    vector<thread> threads;
    threads.resize(threadCount);
    int threadResults[threadCount][wordsPerThread];

    BucketCollection<string, wordAmount, LETTERS> sortedWords = sortWordsByMostFrequentLetter(words);
    const auto bucketIndices = sortedWords.getBucketIndices();
    auto sortedWordsArray = sortedWords.toArray();
    const auto wordHashes = wordsToNumbers(sortedWordsArray);

    int results[wordAmount];

    constexpr int runs = 1000;
    array<chrono::microseconds, runs> times = array<chrono::microseconds, runs>();
    for (int currentRun = 0; currentRun < runs; currentRun++)
    {
        auto start = chrono::high_resolution_clock::now();

        for (int currentThread = 0; currentThread < threadCount; currentThread++)
        {
            threads[currentThread] = thread([&threadResults, &bucketIndices, currentThread, wordAmount, &wordHashes]()
            {
                const int start = wordsPerThread * currentThread;
                const auto currentThreadResults = threadResults[currentThread];
                for (int i = 0; i < wordsPerThread; i++)
                {
                    if (i + start > wordAmount)
                    {
                        break;
                    }

                    const uint32_t firstWord = wordHashes[i+start];
                    int remainingWords = 0;

                    for (int j = 0; j < LETTERS; j++)
                    {
                        if (overlappingLettersWithNumbers(firstWord, 1 << (LETTERS_BY_FREQUENCY[j] - 'A')))
                        {
                            // skip the entire bucket
                            continue;
                        }

                        const int endIndex = j+1 < LETTERS ? bucketIndices[j+1] : wordAmount;
                        for (int k = bucketIndices[j]; k < endIndex; k++)
                        {
                            remainingWords += !overlappingLettersWithNumbers(firstWord, wordHashes[k]);
                        }
                    }

                    currentThreadResults[i] = remainingWords;
                }
            });
        }

        int i = 0;
        int j = 0;
        for (auto& thread : threads)
        {
            thread.join();

            for (const int result : threadResults[i])
            {
                results[j] = result;
                j++;
            }
            i++;
        }
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        times[currentRun] = duration;
    }

    chrono::microseconds minTime = times[0];
    for (const auto& time : times) if (time < minTime) minTime = time;
    cout << "Calculations done! Quickest run took " << minTime << ".\n";
    ranges::sort(ranges::views::zip(sortedWordsArray, results));
    ranges::sort(ranges::views::zip(results, sortedWordsArray));

    ofstream outputFile("results.txt");
    for (int i = 0; i < wordAmount; i++)
    {
        outputFile << sortedWordsArray[i] << " " << results[i] << "\n";
    }
    outputFile.close();

    return 0;
}
