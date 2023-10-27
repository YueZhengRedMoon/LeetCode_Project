#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../debug.h"

class Solution
{
public:
    long long repairCars(std::vector<int> &ranks, int cars)
    {
        std::sort(ranks.begin(), ranks.end());
        long long left = 1, right = (long long)ranks[0] * cars * cars, mid, sum;
        while (left < right)
        {
            sum = 0;
            mid = left + (right - left) / 2;
            for (int r : ranks)
            {
                sum += (long long)std::sqrt(mid / r);
                if (sum >= cars)
                    break;
            }

            if (sum >= cars)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
};

class Solution2
{
public:
    long long repairCars(std::vector<int> &ranks, int cars)
    {
        int count[101]{};
        int minRank = ranks[0];
        for (int r : ranks)
        {
            ++count[r];
            if (r < minRank)
                minRank = r;
        }

        long long left = 1, right = (long long) minRank * cars * cars, mid, sum;
        while (left < right)
        {
            sum = 0;
            mid = left + (right - left) / 2;
            for (int i = 1; i <= 100; ++i)
            {
                sum += (long long) std::sqrt(mid / i) * count[i];
            }
            if (sum >= cars)
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};

int main()
{
    Solution solution;
    std::vector<int> ranks = {5, 1, 8};
    int cars = 6;
    long long ans = solution.repairCars(ranks, cars);
    logObj(ans);
    return 0;
}
