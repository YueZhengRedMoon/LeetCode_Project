#include <iostream>
#include <vector>

class Solution
{
public:
    bool validMountainArray(std::vector<int> &arr)
    {
        if (arr.size() < 3 || arr[0] >= arr[1])
            return false;

        int last = arr[1] - arr[0];
        int extremePoint = 0;   // 极值点的数量
        for (int i = 2; i < arr.size(); ++i)
        {
            int delta = arr[i] - arr[i - 1];
            if (delta == 0)
            {
                return false;
            }
            // 出现极值点
            if (last * delta < 0)
            {
                if (++extremePoint > 1)
                {
                    return false;
                }
            }
            last = delta;
        }

        return extremePoint == 1;
    }
};

class Solution2
{
public:
    bool validMountainArray(std::vector<int> &arr)
    {
        int arrSize = arr.size();
        if (arrSize < 3)
            return false;

        int left = 0;
        int right = arrSize - 1;

        while (left < arrSize - 1 && arr[left] < arr[left + 1]) ++left;

        while (right > 0 && arr[right] < arr[right - 1]) --right;

        return (left == right && left != arrSize - 1 && right != 0);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}