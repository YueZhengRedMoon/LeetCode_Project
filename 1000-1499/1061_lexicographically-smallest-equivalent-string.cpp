#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

class Solution
{
public:
    std::string smallestEquivalentString(std::string s1, std::string s2, std::string baseStr)
    {
        int parent[26];
        std::iota(std::begin(parent), std::end(parent), 0);

        std::function<int(int)> find = [&](int x) -> int {
            if (x == parent[x])
                return x;
            else
                return parent[x] = find(parent[x]);
        };

        std::function<void(char, char)> unite = [&](char c1, char c2) -> void {
            int x = c1 - 'a', y = c2 - 'a';
            x = find(x);
            y = find(y);

            if (x < y)
                parent[y] = x;
            else if (x > y)
                parent[x] = y;
        };

        for (int i = 0; i < s1.size(); ++i)
        {
            unite(s1[i], s2[i]);
        }

        for (int i = 0; i < baseStr.size(); ++i)
        {
            int x = find(baseStr[i] - 'a');
            baseStr[i] = 'a' + x;
        }

        return baseStr;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
