#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    kirie::Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, n = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    kirie::Matrix<int> res = kirie::multiply(m, n);
    debug::printVector2D(res);
    return 0;
}
