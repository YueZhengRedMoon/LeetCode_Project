#include <iostream>
#include <vector>

class Solution
{
public:
    int uniqueLetterString(std::string s)
    {
        // sum = countUniqueChars(s[0:i]) + countUniqueChars(s[1:i]) + ... + countUniqueChars(s[i-1:i])
        std::vector<std::pair<int, int>> lastIndex(26, {-1, -1});
        int n = s.size(), ans = 0, sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int idx = s[i] - 'A';
            sum += (i - lastIndex[idx].second) - (lastIndex[idx].second - lastIndex[idx].first);
            ans += sum;
            lastIndex[idx].first = lastIndex[idx].second;
            lastIndex[idx].second = i;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
