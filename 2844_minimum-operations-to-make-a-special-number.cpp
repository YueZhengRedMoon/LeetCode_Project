#include <iostream>
#include <functional>
#include <algorithm>

class Solution
{
public:

    int minimumOperations(std::string num)
    {
        int len = num.size(), ans = len;

        // 一个数能被25整除，当前仅当其最低2位的数字为00，或25，或50，或75

        std::function<void(char, char)> find = [&](char first, char second) -> void {
            int delCnt = 0;
            bool foundFirst = false;
            for (int i = len - 1; i >= 0 && delCnt < ans; --i)
            {
                if (!foundFirst)
                {
                    if (num[i] == first)
                        foundFirst = true;
                    else
                        ++delCnt;
                }
                else
                {
                    if (num[i] == second)
                    {
                        ans = delCnt;
                        break;
                    }
                    else
                    {
                        ++delCnt;
                    }
                }
            }
        };

        find('0', '0');
        find('5', '2');
        find('0', '5');
        find('5', '7');

        std::find_if(num.begin(), num.end(), [&](char c) -> bool {
            if (c == '0')
            {
                ans = std::min(ans, len - 1);
                return true;
            }
            return false;
        });

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
