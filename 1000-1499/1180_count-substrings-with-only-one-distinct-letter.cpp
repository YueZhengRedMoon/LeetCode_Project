#include <iostream>
#include <unordered_map>

class Solution
{
public:
    int countLetters(std::string s)
    {
        int ans = 0, n = s.size(), i = 0, j;
        while (i < n)
        {
            j = i + 1;
            while (j < n && s[j] == s[i])
                ++j;
            ans += count(j - i);
            i = j;
        }
        return ans;
    }

private:
    std::unordered_map<int, int> memo;

    int count(int len)
    {
        auto it = memo.find(len);
        if (it != memo.end())
            return it->second;

        int res = 0;
        for (int i = 0; i < len; ++i)
        {
            res += len - i;
        }
        return memo[len] = res;
    }
};

class Solution2
{
public:
    int countLetters(std::string s)
    {
        int ans = 0, n = s.size(), i = 0, j;
        while (i < n)
        {
            j = i + 1;
            while (j < n && s[j] == s[i])
                ++j;
            ans += count(j - i);
            i = j;
        }
        return ans;
    }

private:
    int count(int n)
    {
        // 0 + 1 + 2 + ... + n
        return n * (n + 1) / 2;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}