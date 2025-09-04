#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "sorting/mergeSort.hpp"
#include "sorting/parallelMergeSort.hpp"

int main() {
    const int SIZE = 1000000000;

    // Seed RNG
    srand(static_cast<unsigned>(time(0)));

    std::vector<int> nums(SIZE);
    std::vector<int> nums1(SIZE);

    for (int i = 0; i < SIZE; ++i) {
        nums[i] = rand() % 100000000;
        nums1[i] = nums[i];
    }

    // Sequential MergeSort
    MergeSort mergesort(&nums);
    auto start = std::chrono::high_resolution_clock::now();
    mergesort.sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> mergeSortDuration = end - start;

    std::cout << "MergeSort time taken: " << mergeSortDuration.count() << " seconds" << std::endl;

    // Parallel MergeSort
    ParallelMergeSort pmergesort(&nums1);
    start = std::chrono::high_resolution_clock::now();
    pmergesort.sort();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> parallelMergeSortDuration = end - start;

    std::cout << "ParallelMergeSort time taken: " << parallelMergeSortDuration.count() << " seconds" << std::endl;

    // Verify correctness
    if (nums == nums1) {
        std::cout << "Both sorting methods produced identical results ✅" << std::endl;
    } else {
        std::cout << "Mismatch between sorting methods ❌" << std::endl;
    }

    return 0;
}
