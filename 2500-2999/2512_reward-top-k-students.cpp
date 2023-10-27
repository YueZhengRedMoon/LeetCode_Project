#include <iostream>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <queue>
#include <functional>

class Solution
{
public:
    std::vector<int> topStudents(std::vector<std::string> &positiveFeedback,
                                 std::vector<std::string> &negativeFeedback,
                                 std::vector<std::string> &report,
                                 std::vector<int> &studentId, int k)
    {
        std::unordered_set<std::string> positive(positiveFeedback.begin(), positiveFeedback.end());
        std::unordered_set<std::string> negative(negativeFeedback.begin(), negativeFeedback.end());
        // 小顶堆，堆中元素first:学生分数，second:学生ID
        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)>>
        minHeap([](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
            return a.first == b.first ? a.second < b.second : a.first > b.first;
        });

        int n = studentId.size();
        for (int i = 0; i < n; ++i)
        {
            std::istringstream iss(report[i]);
            std::string feedback;
            int score = 0;
            while (iss >> feedback)
            {
                if (positive.find(feedback) != positive.end())
                    score += 3;
                else if (negative.find(feedback) != negative.end())
                    --score;
            }

            minHeap.emplace(score, studentId[i]);
            if (minHeap.size() > k)
                minHeap.pop();
        }

        std::vector<int> ans(k);
        for (int i = k - 1; i >= 0; --i)
        {
            ans[i] = minHeap.top().second;
            minHeap.pop();
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
