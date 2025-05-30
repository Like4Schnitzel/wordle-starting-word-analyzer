#include "words.cpp"
#include <string.h>
#include <algorithm>
#include <ranges>
#include <fstream>
#include <thread>

using namespace std;

int main()
{
    constexpr int threadCount = 16;
    vector<thread> threads;
    threads.reserve(threadCount);
    
    vector<int> results;
    results.resize(words.size());

    static mutex vectorMutex;

    for (int currentThread = 0; currentThread < threadCount; currentThread++)
    {
        threads.emplace_back([&results, currentThread]()
        {
            const int start = words.size() * currentThread / threadCount;
            const int end = words.size() * (currentThread + 1) / threadCount;
            for (int i = start; i < end; i++)
            {
                string firstWord = words[i];
                int remainingWords = 0;

                for (auto checkedWord : words)
                {
                    bool isValid = true;

                    for (auto letter : firstWord)
                    {
                        for (auto checkedLetter : checkedWord)
                        {
                            if (checkedLetter == letter)
                            {
                                isValid = false;
                                break;
                            }
                        }

                        if (!isValid) break;
                    }

                    if (isValid) remainingWords++;
                }

                lock_guard<mutex> lk(vectorMutex);
                results[i] = remainingWords;
            }
        });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    ranges::sort(ranges::views::zip(results, words));
    ofstream outputFile("results.txt");
    for (int i = 0; i < words.size(); i++)
    {
        outputFile << words[i] << " " << results[i] << "\n";
    }
    outputFile.close();

    return 0;
}
