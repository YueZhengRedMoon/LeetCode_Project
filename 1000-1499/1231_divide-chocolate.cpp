#include <iostream>
#include <vector>

class Solution
{
public:
    int maximizeSweetness(std::vector<int>& sweetness, int k)
    {
        int left = sweetness[0], right = sweetness[0], n = sweetness.size();
        for (int i = 1; i < n; ++i)
        {
            right += sweetness[i];
            if (sweetness[i] < left)
                left = sweetness[i];
        }

        int ans = left;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(sweetness, mid, k))   // 可以将巧克力划分为k+1块，使每块的总甜度都>=mid
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return ans;
    }

private:
    // 检查sweetness是否可以划分为k+1块，使每块的的总甜度>=minSweetness
    bool check(const std::vector<int>& sweetness, int minSweetness, int k)
    {
        int sum = 0, cnt = 0;
        for (int i = 0; i < sweetness.size() && cnt <= k; ++i)
        {
            sum += sweetness[i];
            if (sum >= minSweetness)
            {
                ++cnt;
                sum = 0;
            }
        }
        return cnt >= k + 1 || (cnt == k && sum >= minSweetness);
    }
};

int main()
{
    Solution solution;
    std::vector<int> sweetness = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int k = 5;
    int ans = solution.maximizeSweetness(sweetness, k);
    std::cout << ans << std::endl;
    return 0;
}
