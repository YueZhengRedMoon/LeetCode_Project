#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

class Solution
{
public:
    int maxTotalFruits(std::vector<std::vector<int>> &fruits, int startPos, int k)
    {
        // 找到第一坐标大于等于起始位置的水果的索引
        int rightStart = binarySearch(fruits.size(), [&](int mid){return fruits[mid][0] >= startPos;});

        // 从开始位置往右，到达每个水果处能取得水果总数以及需要的步数
        std::vector<std::vector<int>> rightFruits;
        rightFruits.reserve(fruits.size() - rightStart);
        int sum = 0;
        for (int i = rightStart; i < fruits.size() && fruits[i][0] - startPos <= k; ++i)
        {
            sum += fruits[i][1];
            rightFruits.push_back({sum, fruits[i][0] - startPos});
        }

        // 从开始位置往左，到达每个水果处能取得水果总数以及需要的步数
        std::vector<std::vector<int>> leftFruits;
        leftFruits.reserve(rightStart);
        sum = 0;
        for (int i = rightStart - 1; i >= 0 && startPos - fruits[i][0] <= k; --i)
        {
            sum += fruits[i][1];
            leftFruits.push_back({sum, startPos - fruits[i][0]});
        }

        // 直接往右走能获得的最大水果数
        int result = rightFruits.empty() ? 0 : rightFruits.back()[0];

        // 先往左走，然后往右走
        sum = 0;
        for (int i = rightStart - 1; i >= 0; --i)
        {
            // 已经往左走的距离
            int leftSteps = startPos - fruits[i][0];
            if (leftSteps > k)
            {
                break;
            }

            sum += fruits[i][1];
            int currentSum = sum;
            int remain = k - 2 * leftSteps;     // 回到起点后还能走的步数
            // 找到此时往右走最远能走到的位置
            if (remain >= 0 && !rightFruits.empty())
            {
                int rightmost = binarySearch(rightFruits.size(), [&](int mid){return rightFruits[mid][1] >= remain;});
                if (rightmost >= rightFruits.size())
                {
                    currentSum += rightFruits.back()[0];
                }
                else if (rightFruits[rightmost][1] == remain)
                {
                    currentSum += rightFruits[rightmost][0];
                }
                else if (rightmost > 0 && rightFruits[rightmost - 1][1] <= remain)
                {
                    currentSum += rightFruits[rightmost - 1][0];
                }
            }

            if (currentSum > result)
                result = currentSum;
        }

        // 直接往左走能取得的最大水果数
        result = std::max(result, (leftFruits.empty() ? 0 : leftFruits.back()[0]));

        // 先往右走，再往左走
        sum = 0;
        for (int i = rightStart; i < fruits.size(); ++i)
        {
            int rightSteps = fruits[i][0] - startPos;
            if (rightSteps > k)
            {
                break;
            }

            sum += fruits[i][1];
            int currentSum = sum;
            int remain = k - 2 * rightSteps;     // 回到起点后还能走的步数
            if (remain >= 0 && !leftFruits.empty())
            {
                int leftmost = binarySearch(leftFruits.size(), [&](int mid){return leftFruits[mid][1] >= remain;});
                if (leftmost >= leftFruits.size())
                {
                    currentSum += leftFruits.back()[0];
                }
                else if (leftFruits[leftmost][1] == remain)
                {
                    currentSum += leftFruits[leftmost][0];
                }
                else if (leftmost > 0 && leftFruits[leftmost - 1][1] <= remain)
                {
                    currentSum += leftFruits[leftmost - 1][0];
                }
            }

            if (currentSum > result)
                result = currentSum;
        }

        return result;
    }

private:
    int binarySearch(int n, const std::function<bool(int mid)> &comp)
    {
        int left = 0, right = n;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (comp(mid))
            {
                right = mid;
            }
            else
            {
                left  = mid + 1;
            }
        }
        return left;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> fruits = {{0,9},{4,1},{5,7},{6,2},{7,4},{10,9}};
    std::vector<std::vector<int>> fruits2 = {{0,7},{7,4},{9,10},{12,6},{14,8},{16,5},{17,8},{19,4},{20,1},{21,3},{24,3},
                                             {25,3},{26,1},{28,10},{30,9},{31,6},{32,1},{37,5},{40,9}};
    std::vector<std::vector<int>> fruits3 = {{3,2},{7,10},{10,10},{11,2},{13,9},{15,1},{17,1},{22,6},{23,10},{24,6},
                                             {30,8},{33,2},{35,1},{38,5},{39,6}};
    int startPos = 5, k = 4;
    int startPos2 = 21, k2 = 30;
    int startPos3 = 34, k3 = 24;
    int result = solution.maxTotalFruits(fruits, startPos, k);
    std::cout << result << std::endl;
    result = solution.maxTotalFruits(fruits2, startPos2, k2);
    std::cout << result << std::endl;
    result = solution.maxTotalFruits(fruits3, startPos3, k3);
    std::cout << result << std::endl;
    return 0;
}