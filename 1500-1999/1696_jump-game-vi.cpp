#include <iostream>
#include <vector>
#include <deque>

class Solution
{
public:
    int maxResult(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        std::vector<int> f(n);
        f[0] = nums[0];
        std::deque<int> q({0});
        for (int i = 1; i < n; ++i)
        {
            if (q.front() < i - k)
            {
                q.pop_front();
            }

            f[i] = f[q.front()] + nums[i];

            while (!q.empty() && f[i] > f[q.back()])
            {
                q.pop_back();
            }
            q.push_back(i);
        }
        return f[n - 1];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
