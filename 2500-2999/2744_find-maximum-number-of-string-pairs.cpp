#include <iostream>
#include <vector>

class Solution
{
public:
    int maximumNumberOfStringPairs(std::vector<std::string> &words)
    {
        int n = words.size(), ans = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (isMatch(words[i], words[j]))
                    ++ans;
            }
        }
        return ans;
    }

private:
    bool isMatch(const std::string &s1, const std::string &s2)
    {
        if (s1.size() != s2.size())
            return false;
        int n = s1.size();
        for (int i = 0, j = n - 1; i < n; ++i, --j)
        {
            if (s1[i] != s2[j])
                return false;
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
