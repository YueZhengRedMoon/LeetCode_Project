#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

class Solution
{
public:
    int scheduleCourse(std::vector<std::vector<int>> &courses)
    {
        std::sort(courses.begin(), courses.end(), [](const std::vector<int> &lhs, const std::vector<int> & rhs) {
            return lhs[1] < rhs[1]; // 按照lastDay从小到大排序
        });

        std::priority_queue<int> maxHeap;   // 大顶堆
        int day = 0;    // 已消耗的时间
        for (std::vector<int> &course : courses)
        {
            int duration = course[0], lastDay = course[1];
            if (day + duration <= lastDay)  // 没有超过lastDay，直接学习
            {
                day += duration;
                maxHeap.push(duration);
            }
            else if (!maxHeap.empty() && duration < maxHeap.top())  // 该课程学习需要的时间比之前的最长时间要短
            {
                // 反悔，撤销之前学习的duration最长的课程，改为学习该课程
                // 节省的时间能在后面完成更多的课程
                day -= maxHeap.top() - duration;
                maxHeap.pop();
                maxHeap.push(duration);
            }
        }

        return maxHeap.size();
    }
};

// 错误
class Solution2
{
public:
    int scheduleCourse(std::vector<std::vector<int>> &courses)
    {
        int n = courses.size();
        int latestLastDay = 0;  // 最晚截止的课程的截止时间
        std::unordered_map<int, std::vector<int>> lastDayCourse;    // 课程截止时间与课程编号的映射关系
        for (int i = 0; i < n; ++i)
        {
            int lastDay = courses[i][1];
            lastDayCourse[lastDay].push_back(i);
            if (lastDay > latestLastDay)
                latestLastDay = lastDay;
        }

        int ans = 0;
        std::vector<int> dp(latestLastDay + 1, 0);  // dp[i]:第i天结束时最多能学习几门课程
        for (int d = 1; d <= latestLastDay; ++d)
        {
            dp[d] = dp[d - 1];
            auto it = lastDayCourse.find(d);
            if (it != lastDayCourse.end())
            {
                for (int i : it->second)
                {
                    int start = d - courses[i][0];
                    if (start >= 0)
                        dp[d] = std::max(dp[d], dp[start] + 1);
                }
            }
            if (dp[d] > ans)
                ans = dp[d];
        }

        return ans;
    }
};



int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
