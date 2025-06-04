#include <iostream>
#include <vector>
#include <string_view>

class Solution
{
public:
    // 把 word 简称为 s, 把 numFriends 简称为 k
    // 题意：把 s 分割为 k 个非空子串，返回其中最大的子串
    std::string answerString(std::string s, int k)
    {
        if (k == 1)
        {
            // 此时无法分割
            return s;
        }

        int n = s.size();
        std::string_view sView = s;
        std::string_view ansView;
        for (int i = 0; i < n; ++i)
        {
            ansView = std::max(ansView, sView.substr(i, std::min(n - k + 1, n - i)));
        }
        return std::string(ansView);
    }
};

class Solution2
{
public:
    std::string answerString(std::string s, int k)
    {
        if (k == 1)
        {
            // 此时无法分割
            return s;
        }

        int n = s.size();
        std::string ans;
        for (int i = 0; i < n; ++i)
        {
            ans = std::max(ans, s.substr(i, n - std::max(k - 1, i)));
        }
        return ans;
    }
};

class Solution3
{
public:
    std::string answerString(std::string word, int numFriends)
    {
        if (numFriends == 1)
        {
            return word;
        }

        int n = word.size(), i = 0, j = 1;
        while (j < n)
        {
            int k = 0;
            while (j + k < n && word[i + k] == word[j + k])
            {
                ++k;
            }
            if (j + k < n && word[i + k] < word[j + k])
            {
                int t = i;
                i = j;
                j = std::max(j + 1, t + k + 1);
            }
            else
            {
                j += k + 1;
            }
        }

        return word.substr(i, std::min(n - numFriends + 1, n - i));
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
