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

/** 官方二分查找 */
class Solution2
{
public:
    int maxTotalFruits(std::vector<std::vector<int>> &fruits, int startPos, int k)
    {
        // 先往左走x步，再往右走k - x步，此时移动区间是[startPos - x, startPost + k - 2x)
        // 先往右走x步，再往左走k - x步，此时移动区间是[startPos - k + 2x, startPos + x)
        int n = fruits.size();
        std::vector<int> sum(n + 1, 0); // 从左到右水果数量的前缀和
        std::vector<int> indices(n);            // 每个水果的坐标
        for (int i = 0; i < n; ++i)
        {
            sum[i + 1] = sum[i] + fruits[i][1];
            indices[i] = fruits[i][0];
        }

        // 以fruits = {{0,9},{4,1},{5,7},{6,2},{7,4},{10,9}}为例
        // 下标      0       1       2       3       4      5       6
        // sum      0       9       10      17      19     23      32
        // indices   0      4       5       6       7       10      -
        // 当区间为[4, 7]时, start = 1, end = 5, 可以取得的水果数为sum[5]-sum[1] = 23 - 9 = 14

        int ans = 0;
        for (int x = 0; x <= k / 2; ++x)    // 如果要折返，往一个方向最多走k / 2步，否则就回不到起点
        {
            // 向左走x步，再向右走k-x步
            int y = k - 2 * x;  // 回到起点后剩余的步数
            int left = startPos - x;
            int right = startPos + y;
            // 找到第一个大于等于区间左端点的水果坐标的索引
            int start = std::lower_bound(indices.begin(), indices.end(), left) - indices.begin();
            // 找到第一个大于区间右端点的水果坐标的索引
            int end = std::upper_bound(indices.begin(), indices.end(), right) - indices.begin();
            // 计算区间内可以拿到的水果总数
            ans = std::max(ans, sum[end] - sum[start]);

            // 向右走x步，再向左走k - x步
            left = startPos - y;
            right = startPos + x;
            start = std::lower_bound(indices.begin(), indices.end(), left) - indices.begin();
            end = std::upper_bound(indices.begin(), indices.end(), right) - indices.begin();
            ans = std::max(ans, sum[end] - sum[start]);
        }
        return ans;
    }
};

/** 滑动窗口 */
class Solution3
{
public:
    int maxTotalFruits(std::vector<std::vector<int>> &fruits, int startPos, int k)
    {
        int left = 0, right = 0, n = fruits.size(), sum = 0, ans = 0;

        // step(left, right):从startPos出发可以覆盖区间[left, right]的最少移动步数
        auto step = [&](int left, int right) -> int {
            if (fruits[right][0] <= startPos)
                return startPos - fruits[left][0];
            else if (fruits[left][0] >= startPos)
                return fruits[right][0] - startPos;
            else
                return std::min(std::abs(fruits[right][0] - startPos), std::abs(startPos - fruits[left][0]))
                        + fruits[right][0] - fruits[left][0];
        };

        // 每次固定住窗口有边界
        while (right < n)
        {
            sum += fruits[right][1];
            // 移动左边界
            while (left <= right && step(left, right) > k)
            {
                std::cout << "step(" << left << ", " << right << ") = " << step(left, right) << std::endl;
                sum -= fruits[left][1];
                ++left;
            }

            ans = std::max(ans, sum);
            ++right;
        }

        return ans;
    }
};

int main()
{
    Solution3 solution;
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