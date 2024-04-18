#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    std::vector<int> findOriginalArray(std::vector<int>& changed)
    {
        int n = changed.size();
        if (n % 2 == 1)
            return {};

        std::unordered_map<int, int> counter;
        for (int x : changed)
            ++counter[x];

        std::vector<int> original;
        original.reserve(n / 2);
        std::sort(changed.begin(), changed.end(), std::greater<>());   // 从大到小排序
        for (int x : changed)
        {
            std::unordered_map<int, int>::iterator it = counter.find(x);
            if (it->second == 0)    // x已经被用完了
                continue;
            --(it->second); // 当前数被用掉

            if (x % 2)  // x是奇数
            {
                return {};
            }
            else    // x是偶数
            {
                it = counter.find(x / 2);
                if (it != counter.end() && it->second > 0)
                {
                    original.push_back(x / 2);
                    --(it->second); // 用掉x / 2
                }
                else
                {
                    return {};
                }
            }
        }

        return original;
    }
};

class Solution2
{
public:
    std::vector<int> findOriginalArray(std::vector<int>& changed)
    {
        int n = changed.size();
        if (n % 2 == 1)
            return {};

        std::unordered_map<int, int> counter;
        for (int x : changed)
            ++counter[x];

        // 单独处理0
        int cnt0 = counter[0];
        if (cnt0 % 2)
            return {};
        counter.erase(0);
        std::vector<int> original(cnt0 / 2);
        original.reserve(n / 2);

        for (auto it = counter.begin(); it != counter.end(); ++it)
        {
            int x = it->first;
            // 如果x/2在counter中，则跳过
            if (x % 2 == 0 && counter.find(x / 2) != counter.end())
                continue;

            // 把x, 2x, 4x, 8x, ... 全部配对
            while (counter.find(x) != counter.end())
            {
                int cntX = counter[x];
                if (cntX > counter[x * 2])  // 至少需要cntX个2x与x配对
                    return {};
                original.insert(original.end(), cntX, x);
                if (cntX < counter[x * 2])  // 还剩下一些2x
                {
                    counter[2 * x] -= cntX;
                    x *= 2;
                }
                else    // x与2x匹配完了
                {
                    x *= 4;
                }
            }
        }

        return original;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
