#include "words.cpp"
#include "lib.cpp"
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
    const auto wordHashes = wordsToNumbers(words);
    vector<thread> threads;
    threads.reserve(threadCount);
    int threadResults[threadCount][wordsPerThread];
    
    int results[wordAmount];
    auto start = chrono::high_resolution_clock::now();

    for (int currentThread = 0; currentThread < threadCount; currentThread++)
    {
        threads.emplace_back([&threadResults, currentThread, wordAmount, &wordHashes]()
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

                for (const uint32_t checkedWord : wordHashes)
                {
                    remainingWords += !overlappingLettersWithNumbers(firstWord, checkedWord);
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
    cout << "Calculations done! Took " << duration << ".\n";
    
    ranges::sort(ranges::views::zip(results, words));
    ofstream outputFile("results.txt");
    for (int i = 0; i < wordAmount; i++)
    {
        outputFile << words[i] << " " << results[i] << "\n";
    }
    outputFile.close();

    return 0;
}
