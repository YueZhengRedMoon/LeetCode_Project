#include <iostream>
#include <vector>

bool knows(int a, int b);

/** 超时 */
class Solution
{
public:
    int findCelebrity(int n)
    {
        std::vector<int> rowSum(n, 1), colSum(n, 1);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i != j && knows(i, j))
                {
                    ++rowSum[i];
                    ++colSum[j];
                }
            }
        }

        for (int i = 0; i < n; ++i)
        {
            if (rowSum[i] == 1 && colSum[i] == n)
            {
                return i;
            }
        }

        return -1;
    }
};

class Solution2
{
public:
    int findCelebrity(int n)
    {
        // knows(a, b) == true，则a必不是名人（因为他认识别人）
        // knows(a, b) == false， 则b必不是名人（因为有人不认识他）

        // 从左到右，从上到下，遍历邻接矩阵
        // 遇0向右:knows(i, j)=0，j必定不是名人
        // 遇1向下:knows(i, j)=1，i必定不是名人，向下跳转到j，因为<j的人都已经被淘汰

        int i = 0, j;
        for (j = 1; j < n; ++j)
        {
            if (knows(i, j))
                i = j;
        }
        // i可能是名人
        for (--j; j > i; --j)
        {
            if (!knows(j, i))
                return -1;
        }

        for (--j; j >= 0; --j)
        {
            if (!knows(j, i) || knows(i, j))
                return -1;
        }

        return i;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
