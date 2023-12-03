#include <iostream>
#include <vector>

class Solution
{
public:
    int maxScore(std::vector<int> &cardPoints, int k)
    {
        int n = cardPoints.size();
        for (int i = 1; i < n; ++i)
            cardPoints[i] += cardPoints[i - 1];
        if (k == n)
            return cardPoints[n - 1];

        int ans = cardPoints[n - 1] - cardPoints[n - k - 1];
        for (int i = 0; i < k; ++i)
        {
            ans = std::max(ans, cardPoints[i] + cardPoints[n - 1] - cardPoints[n - k + i]);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
