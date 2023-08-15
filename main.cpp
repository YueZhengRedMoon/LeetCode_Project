#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::vector<int> arr{0,5,6,10,8,3,2,19,9,11};
    kirie::MinMaxSegTree segTree(arr);
    logObj(arr.size());
    int qLeft, qRight;
    std::pair<int, int> res;

    res = segTree.query(2, 7);
    logObj(res.first);
    logObj(res.second);

    segTree.update(7, 7);
    res = segTree.query(2, 7);
    logObj(res.first);
    logObj(res.second);
    return 0;
}
