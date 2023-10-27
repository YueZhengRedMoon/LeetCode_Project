#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    /**
     * x1 XOR x2 + y1 XOR y2 = k
     * x1 XOR x2 = i    -> x1 = i XOR x2
     * y1 XOR y2 = k-i  -> y1 = (k-i) XOR y2
     * */

    int countPairs(std::vector<std::vector<int>> &coordinates, int k)
    {
        int ans = 0;
        std::unordered_map<long long, int> cnt;
        for (const std::vector<int> &coordinate : coordinates)
        {
            int x = coordinate[0], y = coordinate[1];
            for (int i = 0; i <= k; ++i)
            {
                auto it = cnt.find(hash(i ^ x, (k - i) ^ y));
                if (it != cnt.end())
                    ans += it->second;
            }
            ++cnt[hash(x, y)];
        }
        return ans;
    }

private:
    long long hash(int x, int y)
    {
        return x * 2000000ll + y;
    }
};

// 超时
class Solution2
{
public:
    int countPairs(std::vector<std::vector<int>> &coordinates, int k)
    {
        int ans = 0, n = coordinates.size();
        for (int i = 0; i < n - 1; ++i)
        {
            int x1 = coordinates[i][0], y1 = coordinates[i][1];
            for (int j = i + 1; j < n; ++j)
            {
                int x2 = coordinates[j][0], y2 = coordinates[j][1];
                if ((x1 ^ x2) + (y1 ^ y2) == k)
                    ++ans;
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
