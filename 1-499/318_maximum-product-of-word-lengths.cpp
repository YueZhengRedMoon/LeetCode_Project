#include <iostream>
#include <vector>

class Solution
{
public:
    int maxProduct(std::vector<std::string> &words)
    {
        int n = words.size();
        std::size_t ans = 0;
        std::vector<int> charSet(n, 0);    // 每个字符串含有的字符的比特集
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < words[i].size() && charSet[i] < 134217727; ++j)    // 134217727 == (1 << 27) - 1
            {
                charSet[i] |= 1 << (words[i][j] - 'a');
            }
        }

        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if ((charSet[i] & charSet[j]) == 0)
                {
                    ans = std::max(ans, words[i].size() * words[j].size());
                }
            }
        }

        return (int) ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
