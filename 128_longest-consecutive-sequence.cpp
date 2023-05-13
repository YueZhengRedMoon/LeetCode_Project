#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int longestConsecutive(std::vector<int> &nums)
    {
        for (int num : nums)
        {
            if (parent.find(num) == parent.end())
            {
                parent[num] = num;
                if (parent.find(num + 1) != parent.end())
                {
                    unite(num, num + 1);
                }

                if (parent.find(num - 1) != parent.end())
                {
                    unite(num - 1, num);
                }
            }
        }

        int ans = 0;
        std::unordered_map<int, int> setSize;
        for (auto it = parent.begin(); it != parent.end(); ++it)
        {
            int x = find(it->first);
            ans = std::max(ans, ++setSize[x]);
        }

        return ans;
    }

private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            return parent[x] = find(parent[x]);
        }
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            return;
        }
        int &rankX = rank[x];
        int &rankY = rank[y];
        if (rankX < rankY)
        {
            parent[x] = y;
        }
        else
        {
            parent[y] = x;
            if (rankX == rankY)
            {
                ++rankX;
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
