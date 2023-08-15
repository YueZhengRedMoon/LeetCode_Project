#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::vector<int> data{0,5,6,10,8,3,2,19,9,11};
    kirie::quickSort<int>(data, 0, data.size() - 1);
    debug::printVector(data);
    return 0;
}
