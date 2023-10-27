#include <iostream>
#include <vector>

class Solution
{
public:
    int minHeightShelves(std::vector<std::vector<int>> &books, int shelfWidth)
    {
        // dp[i]:放i本书需要的最小高度
        std::vector<int> dp(books.size() + 1, 1000000);
        dp[0] = 0;

        for (int i = 1; i <= books.size(); ++i)
        {
            int maxHeight = 0, currentWidth = 0;
            // 将books[j:i]放到新的一层
            for (int j = i; j > 0; --j)
            {
                currentWidth += books[j - 1][0];
                if (currentWidth > shelfWidth)
                {
                    break;
                }
                maxHeight = std::max(maxHeight, books[j - 1][1]);
                dp[i] = std::min(dp[i], dp[j - 1] + maxHeight);
            }
        }

        return dp[books.size()];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
