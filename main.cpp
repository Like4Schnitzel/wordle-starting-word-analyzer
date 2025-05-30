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
    auto start = chrono::high_resolution_clock::now();
    
    constexpr int wordAmount = sizeof(words)/sizeof(*words);
    constexpr int threadCount = 16;
    constexpr int divisibleWordAmount = (1 + wordAmount / threadCount) * threadCount;
    constexpr int wordsPerThread = divisibleWordAmount / threadCount;
    vector<thread> threads;
    threads.reserve(threadCount);
    int threadResults[threadCount][wordsPerThread];

    int results[wordAmount];

    for (int currentThread = 0; currentThread < threadCount; currentThread++)
    {
        threads.emplace_back([&threadResults, currentThread, wordAmount]()
        {
            const int start = wordsPerThread * currentThread;
            for (int i = 0; i < wordsPerThread; i++)
            {
                if (i + start > wordAmount)
                {
                    break;
                }

                const string& firstWord = words[i+start];
                int remainingWords = 0;

                for (const auto& checkedWord : words)
                {
                    if (!overlappingLetters(firstWord, checkedWord))
                    {
                        remainingWords++;
                    }
                }

                threadResults[currentThread][i] = remainingWords;
            }
        });
    }

    int i = 0;
    int j = 0;
    for (auto& thread : threads)
    {
        thread.join();

        for (const auto& result : threadResults[i])
        {
            results[j] = result;
            j++;
        }
        i++;
    }

    ranges::sort(ranges::views::zip(results, words));
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Calculations done! Took " << duration << ".\n";

    ofstream outputFile("results.txt");
    for (int i = 0; i < wordAmount; i++)
    {
        outputFile << words[i] << " " << results[i] << "\n";
    }
    outputFile.close();

    return 0;
}
