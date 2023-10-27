#include <iostream>
#include <vector>

class Solution
{
public:
    int missingElement(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        int left = 0, right = n - 1, should, actual;
        while (left < right)
        {
            int mid = (left + right) >> 1;
            should = nums[mid] - nums[0];   // [nums[0], nums[right]]之间应该有多少个数
            actual = mid;                   // [nums[0], nums[right]]之间实际上有多少个数
            // 缺少的第k个元素不在[nums[0], nums[mid]]中
            if ((should - actual) < k)
            {
                left = mid + 1;
            }
            // 缺少的第k个元素在[nums[0], nums[mid]]中
            else
            {
                right = mid;
            }
        }

        should = nums[right - 1] - nums[0];
        actual = right - 1;
        return nums[right - 1] + k - (should - actual);
    }
};

class Solution2
{
public:
    int missingElement(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        auto missing = [&] (int i) { return nums[i] - nums[0] - i; };   // [nums[0], nums[i]]中缺少的数的数量
        if (k > missing(n - 1))
            return nums[n - 1] + k - missing(n - 1);

        int i = 1;
        while (missing(i) < k)
            ++i;

        return nums[i - 1] + k - missing(i - 1);
    }
};

class Solution3
{
public:
    int missingElement(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        auto missing = [&] (int i) { return nums[i] - nums[0] - i; };   // [nums[0], nums[i]]中缺少的数的数量
        if (k > missing(n - 1))
            return nums[n - 1] + k - missing(n - 1);

        int left = 0, right = n - 1, pivot;
        while (left < right)
        {
            pivot = (left + right) >> 1;
            if (missing(pivot) < k)
                left = pivot + 1;
            else
                right = pivot;
        }

        return nums[left - 1] + k - missing(left - 1);
    }
};

int main()
{

    Solution solution;
    std::vector<int> nums = {579,1310,1398,1416,3122,7035,9969,11310,12331,12431,14767,16391,18880,19076,21852,
                             24586,25923,26166,27577,30132,35266,35725,35836,37829,38186,40457,41100,42646,46495,
                             47729,48671,50593,52151,53794,53882,56666,57228,57309,57358,60247,60577,61247,61313,
                             62047,62082,62290,63576,63600,65137,66535,70613,71589,72605,73379,76078,76344,77946,
                             78047,80729,81023,82304,86531,88189,89768,90541,90791,93103,94343,94466,94597,94778,
                             97455,99439,101282,102659,107706};
    int ans = solution.missingElement(nums, 100000);
    std::cout << ans << std::endl;
    return 0;
}
