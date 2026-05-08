#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

const int MAX_NUM = 1000001;
std::vector<int> primeFactors[MAX_NUM];
// 预处理每个数的质因子列表
int init = [](){
    for (int i = 2; i < MAX_NUM; ++i)
    {
        if (primeFactors[i].empty())    // i 是质数
        {
            for (int j = i; j < MAX_NUM; j += i)
            {
                primeFactors[j].push_back(i);
            }
        }
    }
    return 0;
}();

class Solution
{
public:
    int minJumps(std::vector<int>& nums)
    {
        int n = nums.size();
        std::unordered_map<int, std::vector<int>> groups;
        for (int i = 0; i < n; ++i)
        {
            for (int p : primeFactors[nums[i]]) // 遍历nums[i]的所有质因子
            {
                groups[p].push_back(i); // 对于质数 p，可以跳到下标 i
            }
        }

        std::vector<bool> vis(n, false);
        vis[0] = true;
        std::vector<int> q = {0};
        int ans = 0;
        while (true)
        {
            std::vector<int> tmp = q;
            q.clear();
            for (int i : tmp)
            {
                if (i == n - 1)
                {
                    return ans;
                }

                // nums[i]可以跳到的下标集合
                std::vector<int>& idx = groups[nums[i]];
                idx.push_back(i + 1);
                if (i > 0)
                {
                    idx.push_back(i - 1);
                }

                for (int j : idx)   // 可以从 i 跳到 j
                {
                    if (!vis[j])
                    {
                        vis[j] = true;
                        q.push_back(j);
                    }
                }

                idx.clear();    // 避免重复访问下标列表
            }
            ++ans;
        }
    }
};

namespace MemoryLimit
{
    const int MAX_NUM = 1000001;
    bool isPrime[MAX_NUM];
    int init = [](){
        for (int i = 2; i < MAX_NUM; ++i)
        {
            isPrime[i] = true;
        }
        for (int i = 2; i < MAX_NUM; ++i)
        {
            if (isPrime[i])
            {
                for (int j = i + i; j < MAX_NUM; j += i)
                {
                    isPrime[j] = false;
                }
            }
        }
        return 0;
    }();

    class Solution
    {
    public:
        int minJumps(std::vector<int>& nums)
        {
            int n = nums.size(), maxNum = nums[0];
            std::unordered_map<int, std::vector<int>> pos;
            for (int i = 0; i < n; ++i)
            {
                pos[nums[i]].push_back(i);
                if (nums[i] > maxNum)
                {
                    maxNum = nums[i];
                }
            }

            std::vector<std::vector<int>> jump(n);  // jump[i]:nums[i]可以跳到的下标的集合
            for (int i = 0; i < n; ++i)
            {
                int x = nums[i];
                if (isPrime[x])
                {
                    for (int y = x; y <= maxNum; y += x)
                    {
                        auto it = pos.find(y);
                        if (it != pos.end())
                        {
                            for (int j : it->second)
                            {
                                if (j != i)
                                {
                                    jump[i].push_back(j);
                                }
                            }
                        }
                    }
                }
            }

            std::vector<int> dis(n, n);
            dis[0] = 0;
            std::queue<int> q;
            q.push(0);
            while (!q.empty())
            {
                int i = q.front();
                q.pop();
                if (i == n - 1)
                {
                    return dis[i];
                }

                for (int j : jump[i])
                {
                    if (dis[i] + 1 < dis[j])
                    {
                        dis[j] = dis[i] + 1;
                        q.push(j);
                    }
                }

                if (i && dis[i] + 1 < dis[i - 1])
                {
                    dis[i - 1] = dis[i] + 1;
                    q.push(i - 1);
                }
                if (dis[i] + 1 < dis[i + 1])
                {
                    dis[i + 1] = dis[i] + 1;
                    q.push(i + 1);
                }
            }
            return dis[n - 1];
        }
    };
}

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}