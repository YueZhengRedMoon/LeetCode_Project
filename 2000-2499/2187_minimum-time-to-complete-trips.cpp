#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    long long minimumTime(std::vector<int>& time, int totalTrips)
    {
        std::sort(time.begin(), time.end());    // 升序排序

        long long left = 1, right = (long long) time[0] * totalTrips + 1, ans = (long long) time[0] * totalTrips;
        while (left < right)
        {
            long long mid = left + (right - left) / 2ll;
            if (check(time, totalTrips, mid))
            {
                ans = mid;
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return ans;
    }

private:
    // 检查在给定的时间time内所有公交车是否至少能完成totalTrips趟旅途
    bool check(const std::vector<int>& times, long long totalTrips, long long time)
    {
        long long sum = 0;
        for (long long t : times)
        {
            sum += time / t;
            if (sum >= totalTrips)
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
