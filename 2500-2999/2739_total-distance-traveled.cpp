#include <iostream>
#include <vector>

class Solution
{
public:
    int distanceTraveled(int mainTank, int additionalTank)
    {
        int ans = 0;
        while (mainTank)
        {
            int d;
            if (mainTank >= 5)
            {
                d = 5;
                if (additionalTank)
                {
                    ++mainTank;
                    --additionalTank;
                }
            }
            else
            {
                d = mainTank;
            }
            mainTank -= d;
            ans += d * 10;
        }
        return ans;
    }
};

class Solution2
{
public:
    int distanceTraveled(int mainTank, int additionalTank)
    {
        int ans = 0;
        while (mainTank >= 5)
        {
            int t = mainTank / 5;
            ans += t * 50;
            mainTank %= 5;
            t = std::min(t, additionalTank);
            additionalTank -= t;
            mainTank += t;
        }
        return ans + mainTank * 10;
    }
};

class Solution3
{
public:
    int distanceTraveled(int mainTank, int additionalTank)
    {
        // 考虑从副油箱能得到多少燃料。
        // 主油箱消耗5升燃料可以从副油箱得到1升，这一升又加回到主油箱
        // 相当于在主油箱剩余燃料>=5时，每消耗4升燃料，可以从副油箱获得一升燃料
        return 10 * (mainTank + std::min((mainTank - 1) / 4, additionalTank));
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
