#include "bucketCollection.hpp"

template <typename T, size_t n, size_t m>
BucketCollection<T, n, m>::BucketCollection(std::array<std::vector<T>, m>& buckets)
{
    this->buckets = buckets;
    this->totalIndex = 0;
    this->bucketIndex = 0;
    this->currentBucket = 0;
}

template <typename T, size_t n, size_t m>
constexpr int BucketCollection<T, n, m>::size()
{
    return n;
}

template <typename T, size_t n, size_t m>
int BucketCollection<T, n, m>::getTotalIndex()
{
    return n;
}

template <typename T, size_t n, size_t m>
int BucketCollection<T, n, m>::getCurrentBucket()
{
    return this->currentBucket;
}

template <typename T, size_t n, size_t m>
std::array<std::vector<T>, m>& BucketCollection<T, n, m>::getBuckets()
{
    return this->buckets;
}

template <typename T, size_t n, size_t m>
std::array<int, m> BucketCollection<T, n, m>::getBucketIndices()
{
    std::array<int, m> result;

    result[0] = 0;
    for (int i = 1; i < m; i++)
    {
        result[i] = result[i-1] + buckets[i-1].size();
    }

    return result;
}

template <typename T, size_t n, size_t m>
const T& BucketCollection<T, n, m>::next()
{
    if (bucketIndex >= this->buckets[currentBucket].size())
    {
        this->skipBucket();
    }

    totalIndex++;
    return buckets[currentBucket][bucketIndex++];
}

template <typename T, size_t n, size_t m>
void BucketCollection<T, n, m>::skipBucket()
{
    totalIndex += buckets[currentBucket].size() - bucketIndex;
    bucketIndex = 0;
    currentBucket++;
}

template <typename T, size_t n, size_t m>
std::array<T, n> BucketCollection<T, n, m>::toArray()
{
    std::array<T, n> result;
    int i = 0;

    for (const auto& bucket : buckets)
    {
        for (const T& item : bucket)
        {
            result[i] = item;
            i++;
        }
    }

    return result;
}
