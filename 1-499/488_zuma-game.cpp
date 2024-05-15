#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

class Solution
{
public:
    int findMinStep(std::string board, std::string hand)
    {
        std::sort(hand.begin(), hand.end());
        int ans = dfs(board, hand);
        return ans <= 5 ? ans : -1;
    }

private:
    std::unordered_map<std::string, int> memo;

    int dfs(const std::string& board, const std::string& hand)
    {
        int boardSize = board.size(), handSize = hand.size();
        if (boardSize == 0)
            return 0;
        std::string key = board + " " + hand;
        auto it = memo.find(key);
        if (it != memo.end())
            return it->second;

        int res = 6;
        for (int j = 0; j < handSize; ++j)  // 枚举打出去的球
        {
            // 第1个剪枝条件：当前选择的球的颜色和前一个球的颜色相同
            if (j > 0 && hand[j] == hand[j - 1])
                continue;

            std::string newHand = hand.substr(0, j) + hand.substr(j + 1);
            for (int i = 0; i <= boardSize; ++i)    // 枚举插入的位置
            {
                // 第2个剪枝条件：只在连续相同颜色的球的开头位置插入新球
                if (i > 0 && board[i - 1] == hand[j])
                    continue;

                bool choose = false;
                // 第3个剪枝条件：只在以下两种情况放置新球
                //  - 情况1：当前球颜色与后面的球的颜色相同
                if (i < boardSize && board[i] == hand[j])
                    choose = true;
                // 情况2：当前后颜色相同且与当前颜色不同的时候放置球
                if (i > 0 && i < boardSize && board[i - 1] == board[i] && board[i] != hand[j])
                    choose = true;

                if (choose)
                {
                    std::string newBoard = clean(board.substr(0, i) + hand[j] + board.substr(i), i, i);
                    res = std::min(res, dfs(newBoard, newHand) + 1);
                }
            }
        }

        return memo[key] = res;
    }

    std::string clean(const std::string& board, int x, int y)
    {
        int n = board.size();
        if (x < 0 || y >= n || board[x] != board[y])
            return board;

        int i = x;
        while (i >= 0 && board[i] == board[x])
            --i;

        int j = y;
        while (y < n && board[j] == board[y])
            ++j;

        if (j - i - 1 >= 3)
        {
            // board(i, j)可以消除
            return clean(board.substr(0, i + 1) + board.substr(j), i, i + 1);
        }

        return board;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
