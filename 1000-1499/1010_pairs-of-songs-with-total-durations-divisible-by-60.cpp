#include <iostream>
#include <vector>

/** 超时 */
class Solution
{
public:
    int numPairsDivisibleBy60(std::vector<int> &time)
    {
        int size = time.size();
        int num = 0;
        for (int i = 0; i < size - 1; ++i)
        {
            for (int j = i + 1; j < size; ++j)
            {
                if ((time[i] + time[j]) % 60 == 0)
                {
                    ++num;
                }
            }
        }
        return num;
    }
};

class Solution2
{
public:
    int numPairsDivisibleBy60(std::vector<int> &time)
    {
        int size = time.size();
        std::vector<std::vector<int>> count(size + 1, std::vector<int>(60, 0));
        for (int i = size - 1; i >= 1; --i)
        {
            for (int j = 0; j < 60; ++j)
            {
                count[i][j] = count[i + 1][j];
            }

            ++count[i][time[i] % 60];
        }

        int result = 0;
        for (int i = 0; i < size - 1; ++i)
        {
            result += count[i + 1][(60 - time[i] % 60) % 60];
        }
        return result;
    }
};

class Solution3
{
public:
    int numPairsDivisibleBy60(std::vector<int> &time)
    {
        int count[60] = {0};
        for (int t : time)
        {
            ++count[t % 60];
        }

        long long result = 0;
        for (int i = 1; i < 30; ++i)
        {
            result += count[i] * count[60 - i];
        }
        result += static_cast<long long>(count[0]) * (count[0] - 1) / 2 + static_cast<long long>(count[30]) * (count[30] - 1) / 2;
        return static_cast<int>(result);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}