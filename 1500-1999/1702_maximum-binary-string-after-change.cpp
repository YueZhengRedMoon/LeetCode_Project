#include <iostream>
#include <vector>

class Solution
{
public:
    std::string maximumBinaryString(std::string binary)
    {
        int zeroCnt = 0, firstZeroPos = -1, n = binary.size();
        for (int i = 0; i < n; ++i)
        {
            if (binary[i] == '0')
            {
                ++zeroCnt;
                if (firstZeroPos == -1)
                    firstZeroPos = i;
            }
        }
        if (firstZeroPos == -1)
            return binary;
        std::string ans(n, '1');
        ans[firstZeroPos + zeroCnt - 1] = '0';
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
