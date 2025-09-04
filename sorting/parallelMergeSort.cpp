#include "parallelMergeSort.hpp"
#include <thread>
#include <algorithm> // for std::sort


ParallelMergeSort::ParallelMergeSort(std::vector<int> *nums) 
    : nums(nums) {}

ParallelMergeSort::~ParallelMergeSort() {}

void ParallelMergeSort::recursiveSort(int left, int right) {
    const int BASE_THRESHOLD = 5000;     // below this, just std::sort
    const int THREAD_THRESHOLD = 50000;  // below this, no new threads

    if (left >= right) return;

    // small segment: use std::sort directly
    if (right - left < BASE_THRESHOLD) {
        std::sort(nums->begin() + left, nums->begin() + right + 1);
        return;
    }

    int mid = left + (right - left) / 2;

    if (right - left > THREAD_THRESHOLD) {
        // spawn two threads
        std::thread t1([this, left, mid] { recursiveSort(left, mid); });
        std::thread t2([this, mid, right] { recursiveSort(mid + 1, right); });
        t1.join();
        t2.join();
    } else {
        // sequential recursion
        recursiveSort(left, mid);
        recursiveSort(mid + 1, right);
    }

    // merge step
    std::vector<int> result;
    result.reserve(right - left + 1);

    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if ((*nums)[i] <= (*nums)[j]) {
            result.push_back((*nums)[i++]);
        } else {
            result.push_back((*nums)[j++]);
        }
    }
    while (i <= mid) result.push_back((*nums)[i++]);
    while (j <= right) result.push_back((*nums)[j++]);

    for (int k = 0; k < (int)result.size(); k++) {
        (*nums)[left + k] = result[k];
    }
}

void ParallelMergeSort::sort() {
    if (nums->empty()) return;
    recursiveSort(0, nums->size() - 1);
}
