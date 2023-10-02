#include <iostream>
#include <vector>

class Solution
{
public:
    std::string maximumOddBinaryNumber(std::string s)
    {
        int len = s.size(), i ,j = len - 2;
        if (s.back() == '0')    // s表示的数是偶数
        {
            // 将最低为的1交换到最低为，先将s代表的数转变为奇数
            for (i = len - 2; i >= 0; --i)
            {
                if (s[i] == '1')
                {
                    j = i - 1;
                    std::swap(s[i], s[len - 1]);
                    break;
                }
            }
        }

        i = 0;
        while (i < j)
        {
            // 跳过高位的1
            while (i < j && s[i] == '1')
                ++i;
            // 跳过低位的0
            while (i < j && s[j] == '0')
                --j;
            // 将高位的0与低位的1交换
            if (i < j)
                std::swap(s[i], s[j]);
        }

        return s;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
