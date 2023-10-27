#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int numFactoredBinaryTrees(std::vector<int> &arr)
    {
        const int MOD = 1e9 + 7;
        std::unordered_map<int, int> count; // count[k]:以k为根节点的二叉树的数量
        int ans = 0, n = arr.size();
        for (int val : arr)
        {
            count[val] = 1;
            ++ans;
        }

        std::sort(arr.begin(), arr.end());
        for (int i = 1; i < n; ++i) // 枚举根节点
        {
            int &root = count[arr[i]];
            for (int j = 0; j < i; ++j) // 枚举其中一个子节点
            {
                int another = arr[i] / arr[j];  // 另一个子节点
                if (another < arr[j])
                    break;
                if (count.find(another) == count.end() || another * arr[j] != arr[i])
                    continue;

                long long newCnt = (arr[j] == another ? 1ll : 2ll) * count[arr[j]] * count[another] % MOD;
                ans = (ans + newCnt) % MOD;
                root = (root + newCnt) % MOD;
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
