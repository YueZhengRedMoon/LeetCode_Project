#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Solution
{
public:
    int medianOfUniquenessArray(std::vector<int>& nums)
    {
        long long n = nums.size();
        long long k = ((n * (n + 1) / 2) + 1) / 2;
        int left = 1, right = std::unordered_set<int>(nums.begin(), nums.end()).size(), ans = 0;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (check(mid, nums, k))
            {
                ans = mid;
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return ans;
    }

private:
    // 检查nums中是否至少存在k个子数组满足子数组中不同元素的个数<=upper
    bool check(int upper, const std::vector<int>& nums, long long k)
    {
        int l = 0;
        long long cnt = 0;
        std::unordered_map<int, int> freq;
        for (int r = 0; r < nums.size(); ++r)
        {
            int in = nums[r];
            ++freq[in];
            while (freq.size() > upper)
            {
                int out = nums[l++];
                if (--freq[out] == 0)
                {
                    freq.erase(out);
                }
            }
            cnt += r - l + 1;   // 右端点为r时，有k - l + 1个合法的左端点，使得区间内元素的种数<= upper
            if (cnt >= k)
                return true;
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
