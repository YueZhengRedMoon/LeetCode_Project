#include <iostream>
#include <vector>

void printVector(const std::vector<int>& nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
}

class Solution
{
public:
    int candy(std::vector<int> &ratings)
    {
        std::vector<int> candyVec(ratings.size(), 1);
        // 从左到右
        for (int i = 1; i < ratings.size(); ++i)
        {
            if (ratings[i] > ratings[i - 1])
            {
                candyVec[i] = candyVec[i - 1] + 1;
            }
        }
        // 从右向左
        for (int i = ratings.size() - 2; i >= 0; --i)
        {
            if (ratings[i] > ratings[i + 1])
            {
                candyVec[i] = std::max(candyVec[i], candyVec[i + 1] + 1);
            }
        }
        // 统计结果
        int result = 0;
        for (int count : candyVec)
        {
            result += count;
        }
        return result;
    }
};

int main()
{
    // 15 1 2 3  3 3 2 3 4 4 3 3 3 1 2 2
    // 7 1 6 10 8 7 3 2
    // 5 1 3 4 5 2
    std::vector<int> ratings;
    int n, rating;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> rating;
        ratings.push_back(rating);
    }

    Solution solution;
    std::cout << solution.candy(ratings) << std::endl;
    return 0;
}
