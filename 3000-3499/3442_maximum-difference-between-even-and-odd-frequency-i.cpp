#include <iostream>
#include <vector>

class Solution
{
public:
    int maxDifference(std::string s)
    {
        const int MAX_LEN = 101;
        int counter[26]{0};
        for (char c : s)
        {
            ++counter[c - 'a'];
        }
        int maxOdd = 0, minEven = MAX_LEN;
        for (int i = 0; i < 26; ++i)
        {
            if (counter[i] % 2 == 0)    // 出现偶数次
            {
                if (counter[i] && counter[i] < minEven)
                    minEven = counter[i];
            }
            else    // 出现奇数次
            {
                if (counter[i] > maxOdd)
                    maxOdd = counter[i];
            }
        }

        return maxOdd - minEven;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
