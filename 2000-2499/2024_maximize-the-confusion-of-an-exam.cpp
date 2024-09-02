#include <iostream>
#include <vector>

class Solution
{
public:
    int maxConsecutiveAnswers(std::string answerKey, int k)
    {
        int ans = 1, cntT = answerKey[0] == 'T', cntF = answerKey[0] == 'F';
        for (int i = 0, j = 1; j < answerKey.size(); ++j)
        {
            if (answerKey[j] == 'T')
                ++cntT;
            else
                ++cntF;
            while (std::min(cntT, cntF) > k)
            {
                if (answerKey[i++] == 'T')
                    --cntT;
                else
                    --cntF;
            }
            ans = std::max(ans, j - i + 1);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
