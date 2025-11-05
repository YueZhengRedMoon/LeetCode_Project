#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

class Solution
{
public:
    using Pair = std::pair<int, int>;   // first:出现次数，second:元素值

    std::vector<long long> findXSum(std::vector<int>& nums, int k, int x)
    {
        int n = nums.size();
        std::vector<long long> ans(n - k + 1);
        for (int r = 0; r < n; ++r) // 枚举滑动窗口的右端点
        {
            // 添加in
            int in = nums[r];
            del(in);
            ++cnt[in];
            add(in);

            int l = r + 1 - k;  // 滑动窗口的左端点
            if (l < 0)
            {
                continue;
            }

            while (!rSet.empty() && lSet.size() < x)
            {
                r2l();
            }
            while (lSet.size() > x)
            {
                l2r();
            }
            ans[l] = sumL;

            // 移除out
            int out = nums[l];
            del(out);
            --cnt[out];
            add(out);
        }
        return ans;
    }

private:
    std::set<Pair> lSet;
    std::set<Pair> rSet;
    long long sumL{0}; // lSet的元素和
    std::unordered_map<int, int> cnt;

    // 在lSet和rSet维护的Pairs中增加{cnt[x], x}
    void add(int x)
    {
        Pair p = {cnt[x], x};
        if (p.first == 0)
        {
            return;
        }

        if (!lSet.empty() && p > * lSet.begin())    // p(={cnt[x],x}) 比 lSet中最小的{cnt[y],y}还大
        {
            sumL += (long long) p.first * p.second;
            lSet.insert(p);
        }
        else    // p(={cnt[x],x}) 比 lSet中最小的{cnt[y],y}小
        {
            rSet.insert(p);
        }
    }

    // 在lSet和rSet维护的Pairs中删除{cnt[x], x}
    void del(int x)
    {
        Pair p = {cnt[x], x};
        if (p.first == 0)
        {
            return;
        }

        auto it = lSet.find(p);
        if (it != lSet.end())
        {
            sumL -= (long long) p.first * p.second;
            lSet.erase(it);
        }
        else
        {
            rSet.erase(p);
        }
    }

    // 将lSet中最小的{cnt[x], x}移动到rSet中
    void l2r()
    {
        Pair p = *lSet.begin();
        sumL -= (long long) p.first * p.second;
        lSet.erase(lSet.begin());
        rSet.insert(p);
    }

    // 将rSet中最大的{cnt[x], x}移动到lSet中
    void r2l()
    {
        Pair p = *rSet.rbegin();
        sumL += (long long) p.first * p.second;
        rSet.erase(p);
        lSet.insert(p);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}