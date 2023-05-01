#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

/** 超时 */
class Solution
{
public:
    int nthUglyNumber(int n)
    {
        if (n <= 6)
        {
            return n;
        }
        std::vector<bool> isUgly(7, true);
        isUgly.reserve(n * 5);

        int count = 6, i, result;
        for (i = 7; count < n; ++i)
        {
            if ((i % 2 == 0 && isUgly[i / 2]) ||
                (i % 3 == 0 && isUgly[i / 3]) ||
                (i % 5 == 0 && isUgly[i / 5]))
            {
                isUgly.push_back(true);
                ++count;
                result = i;
            }
            else
            {
                isUgly.push_back(false);
            }
        }

        return result;
    }
};

class Solution2
{
public:
    int nthUglyNumber(int n)
    {
        if (n <= 6)
        {
            return n;
        }

        int factors[] = {2, 3, 5};
        std::priority_queue<long long, std::vector<long long>, std::greater<> > heap;
        std::unordered_set<long long> seen;
        heap.push(1ll);
        seen.insert(1ll);
        long long ugly = 0;
        for (int i = 0; i < n; ++i)
        {
            ugly = heap.top();
            heap.pop();

            for (int factor : factors)
            {
                if (seen.insert(ugly * factor).second)
                {
                    heap.push(ugly * factor);
                }
            }
        }

        return static_cast<int>(ugly);
    }
};

int main()
{
    int n;
    std::cin >> n;
    Solution2 solution;
    int result = solution.nthUglyNumber(n);
    std::cout << result << std::endl;
    return 0;
}