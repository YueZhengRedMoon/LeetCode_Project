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

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
