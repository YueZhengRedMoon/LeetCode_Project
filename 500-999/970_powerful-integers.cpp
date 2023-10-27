#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    std::vector<int> powerfulIntegers(int x, int y, int bound)
    {
        // 存放x的n次方
        std::vector<int> xn = {1};
        if (x > 1)
        {
            int xi = 1;
            for (int i = 1; xi < bound; ++i)
            {
                xi *= x;
                xn.push_back(xi);
            }
        }

        // 存放y的n次方
        std::vector<int> yn = {1};
        std::vector<int> &ryn = (x == y ? xn : yn);
        if (x != y && y > 1)
        {
            int yi = 1;
            for (int i = 1; yi < bound; ++i)
            {
                yi *= y;
                yn.push_back(yi);
            }
        }

        std::unordered_set<int> powerful;
        for (int xi : xn)
        {
            for (int yi : ryn)
            {
                if (xi + yi <= bound)
                {
                    powerful.emplace(xi + yi);
                }
            }
        }

        return std::vector<int>(powerful.begin(), powerful.end());
    }
};

class Solution2
{
public:
    std::vector<int> powerfulIntegers(int x, int y, int bound)
    {
        // 存放x的n次方
        std::vector<int> xn = {1};
        if (x > 1)
        {
            int xi = 1;
            for (int i = 1; xi < bound; ++i)
            {
                xi *= x;
                xn.push_back(xi);
            }
        }

        // 存放y的n次方
        std::vector<int> yn = {1};
        std::vector<int> &ryn = (x == y ? xn : yn);
        if (x != y && y > 1)
        {
            int yi = 1;
            for (int i = 1; yi < bound; ++i)
            {
                yi *= y;
                yn.push_back(yi);
            }
        }

        int count = 0;  // 强整数的数量
        std::vector<int> isPowerful(bound + 1, false);
        for (int xi : xn)
        {
            for (int yi : ryn)
            {
                int sum = xi + yi;
                if (sum <= bound)
                {
                    if (!isPowerful[sum])
                    {
                        ++count;
                    }
                    isPowerful[sum] = true;
                }
                else
                {
                    break;
                }
            }
        }

        std::vector<int> result;
        result.reserve(count);
        for (int i = 2; i <= bound; ++i)
        {
            if (isPowerful[i])
            {
                result.push_back(i);
            }
        }

        return result;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}