#include <iostream>
#include <vector>

class Solution
{
public:
    int distMoney(int money, int children)
    {
        if (money < children)
            return -1;

        int ans;
        money -= children;                          // 每个人先发一元
        int x = std::min(money / 7, children);      // 可以给x个人发7元，正好凑到8元
        int y = children - x;                       // 还剩y个人，它们各持有1元
        int r = money - 7 * x;                      // 给x个人发完7元，还剩下的钱
        // 每个人目前都正好有8元，如果还有剩余的钱，则会有至少一个人因为多拿钱而不是正好拿8元
        if (y == 0)
            ans = std::max(x - (r > 0), 0);
        // 如果正好还剩一个人，且还剩3元，则必须从前面x个人中拿出1元给最后一个人，避免是最后一个人正好拿4元
        else if (r == 3 && y == 1)
            ans = std::max(x - 1, 0);
        // 在剩下的情况中，总能有方案可以不改变x个人的钱，并使剩下的y个人中没有人正好拿4元
        else
            ans = x;
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
