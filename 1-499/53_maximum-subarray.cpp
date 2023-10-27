#include <iostream>
#include <vector>

class Solution
{
public:
    struct Status
    {
        int lSum;   // [l, r]内以l为左端点的最大子段和
        int rSum;   // [l, r]内以r为右端点的最大字段和
        int mSum;   // [l, r]内的最大子段和
        int iSum;   // [l, r]的区间和
    };

    int maxSubArray(std::vector<int> &nums)
    {
        return get(nums, 0, nums.size() -1).mSum;
    }

private:
    Status pushUp(Status l, Status r)
    {
        int iSum = l.iSum + r.iSum;
        int lSum = std::max(l.lSum, l.iSum + r.lSum);
        int rSum = std::max(r.rSum, r.iSum + l.rSum);
        int mSum = std::max(std::max(l.mSum, r.mSum), l.rSum + r.lSum);
        return {lSum, rSum, mSum, iSum};
    }

    Status get(std::vector<int> &a, int l, int r)
    {
        if (l == r)
        {
            return {a[l], a[l], a[l], a[l]};
        }
        int m = (l + r) >> 1;   // m = (l + r) / 2
        Status lSub = get(a, l, m);
        Status rSub = get(a, m + 1, r);
        return pushUp(lSub, rSub);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
