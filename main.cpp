#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::vector<std::vector<int>> arr = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    kirie::MatrixSum arrSum(arr);
    arrSum.printSum();
    logObj(arrSum.query(0, 1, 2, 3));
    return 0;
}
