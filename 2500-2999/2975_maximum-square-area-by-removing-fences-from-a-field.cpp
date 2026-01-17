#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution
{
public:
    int maximizeSquareArea(int m, int n, std::vector<int>& hFences, std::vector<int>& vFences)
    {
        // 对于水平栅栏，任意两个栅栏之间的距离（中间的栅栏全部删除）都可能是正方形的边长，存到哈希表 hSet 中
        std::unordered_set<int> hSet = f(hFences, m);

        // 对于垂直栅栏，任意两个栅栏之间的距离（中间的栅栏全部删除）都可能是正方形的边长，存到哈希表 vSet 中
        std::unordered_set<int> vSet = f(vFences, n);

        // 答案是 hSet 和 vSet 交集中的最大值的平方
        int maxSide = 0;
        for (int x : hSet)
        {
            if (vSet.find(x) != vSet.end() && x > maxSide)
            {
                maxSide = x;
            }
        }
        return maxSide ? (long long) maxSide * maxSide % 1'000'000'007 : -1;
    }

private:
    // 计算a中的栅栏加上1号和mx号栅栏后，任意两个栅栏之间距离的值的集合
    std::unordered_set<int> f(std::vector<int>& a, int mx)
    {
        a.push_back(1);
        a.push_back(mx);
        std::sort(a.begin(), a.end());

        // 计算 a 中任意两个数的差，保存到哈希集合中
        std::unordered_set<int> set;
        for (int i = 0; i < a.size(); ++i)
        {
            for (int j = i + 1; j < a.size(); ++j)
            {
                set.insert(a[j] - a[i]);
            }
        }
        return set;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}