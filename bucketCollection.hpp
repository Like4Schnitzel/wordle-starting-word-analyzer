#include <vector>
#include <array>
#pragma once

template <typename T, size_t n, size_t m>
class BucketCollection {
private:
    int totalIndex;
    int bucketIndex;
    int currentBucket;
    std::array<std::vector<T>, m> buckets;
public:
    BucketCollection(std::array<std::vector<T>, m>& buckets);
    constexpr int size();
    int getTotalIndex();
    int getCurrentBucket();
    std::array<std::vector<T>, m>& getBuckets();
    std::array<int, m> getBucketIndices();
    const T& next();
    void skipBucket();
    std::array<T, n> toArray();
};

#include "bucketCollection.tpp"
