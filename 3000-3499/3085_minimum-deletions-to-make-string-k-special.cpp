#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minimumDeletions(std::string word, int k)
    {
        const int SIGMA = 26;
        int cnt[SIGMA]{};
        for (char c : word)
        {
            ++cnt[c - 'a'];
        }
        std::sort(std::begin(cnt), std::end(cnt));

        int maxSave = 0;
        for (int i = 0; i < SIGMA; ++i)
        {
            int sum = 0;
            for (int j = i; j < SIGMA; ++j)
            {
                sum += std::min(cnt[j], cnt[i] + k);
            }
            maxSave = std::max(maxSave, sum);
        }

        return word.size() - maxSave;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
