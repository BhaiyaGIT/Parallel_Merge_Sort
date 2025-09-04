#include "mergeSort.hpp"

MergeSort::MergeSort(std::vector<int> *nums) {
    this->nums = nums;
}

MergeSort::~MergeSort() {}

void MergeSort::recursiveSort(int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;

    recursiveSort(left, mid);
    recursiveSort(mid + 1, right);

    std::vector<int> result;
    result.reserve(right - left + 1);  

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if ((*nums)[i] <= (*nums)[j]) {
            result.push_back((*nums)[i++]);
        } else {
            result.push_back((*nums)[j++]);
        }
    }

    while (i <= mid) {
        result.push_back((*nums)[i++]);
    }

    while (j <= right) {
        result.push_back((*nums)[j++]);
    }

    for (int k = 0; k < (int)result.size(); k++) {
        (*nums)[left + k] = result[k];
    }
}

void MergeSort::sort() {
    if (nums->empty()) {
        return;  
    }
    recursiveSort(0, nums->size() - 1);
}
