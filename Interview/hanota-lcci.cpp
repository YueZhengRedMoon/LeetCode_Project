#include <iostream>
#include <vector>

class Solution
{
public:
    void hanota(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C)
    {
        move(A.size(), A, B, C);
    }

private:
    // 将A中的n个盘子通过B移动到C中
    void move(int n, std::vector<int>& A, std::vector<int>& B, std::vector<int>& C)
    {
        // A柱子只有一个盘子，将其移动到C盘
        if (n == 1)
        {
            C.push_back(A.back());
            A.pop_back();
        }
        else
        {
            // 将n - 1个盘子从A通过C移动到B
            move(n - 1, A, C, B);
            // 将A中剩下的最大的盘子移到C盘
            C.push_back(A.back());
            A.pop_back();
            // 将B中的n - 1个盘子通过空的A移动到C
            move(n - 1, B, A, C);
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
