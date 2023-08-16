#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    int n = 21;
    std::vector<std::vector<int>> factors(n);
    for (int i = 2; i < n; ++i)
    {
        if (factors[i].empty())
        {
            for (int j = i; j < n; j += i)
            {
                factors[j].push_back(i);
            }
        }
    }
    for (int i = 2; i < n; ++i)
    {
        std::cout << i << " : ";
        debug::printVector(factors[i]);
    }
    return 0;
}
