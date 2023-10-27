#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    std::vector<int> sortByBits(std::vector<int> &arr)
    {
        // 每种数对应的二进制表示中1的个数
        std::unordered_map<int, int> oneCount;
        for (int num : arr)
        {
            if (oneCount.find(num) == oneCount.end())
            {
                oneCount[num] = getOneCount(num);
            }
        }

        std::sort(arr.begin(), arr.end(), [&oneCount](int lhs, int rhs){
            int lhsOneCount = oneCount[lhs];
            int rhsOneCount = oneCount[rhs];
            if (lhsOneCount == rhsOneCount)
            {
                return lhs < rhs;
            }
            else
            {
                return lhsOneCount < rhsOneCount;
            }
        });

        return arr;
    }

private:
    int getOneCount(int num)
    {
        // num的值最大取到10^4，即0010 0111 0001 0000
        int count = 0;
        int temp = 1;
        if (num & temp) ++count;
        for (int i = 1; i <= 13; ++i)
        {
            temp <<= 1;
            if (num & temp) ++count;
        }
        return count;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}