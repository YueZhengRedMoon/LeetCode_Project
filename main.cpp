#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"

int main()
{
    std::vector<int> vec = {1, 3, 4, 6, 9, 14, 16, 27, 30, 32, 35};
    int maxIndex = kirie::maxLessEqual(vec.size(), [&](int mid) {
        return vec[mid] < 30;
    });
    std::cout << "maxIndex = " << maxIndex << ", vec[maxIndex] = " << vec[maxIndex] << std::endl;
    int minIndex = kirie::minGreaterEqual(vec.size(), [&](int mid){
        return vec[mid] >= 16;
    });
    std::cout << "minIndex = " << minIndex << ", vec[minIndex] = " << vec[minIndex] << std::endl;

    std::cout << kirie::max(23, 47, 17, 98, 20) << std::endl;
    return 0;
}
