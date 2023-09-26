#include <iostream>
#include <vector>

class Solution
{
public:
    int passThePillow(int n, int time)
    {
        int roundStep = n - 1;              // 从队列的一段传递到另一段传递的次数
        int roundCount = time / roundStep;  // 从队列的一端传递到另一段的次数
        int remain = time % roundStep;      // 最后一轮剩下的传递次数
        if (roundCount % 2 == 0)
        {
            return 1 + remain;
        }
        else
        {
            return n - remain;
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
