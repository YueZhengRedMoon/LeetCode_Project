#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
    int maximumGain(std::string s, int x, int y)
    {
        int n = s.size();

        // 假设x>=y,否则将s中的a替换为b,b替换为a,然后交换x,y
        if (x < y)
        {
            for (int i = 0; i < n; ++i)
            {
                if (s[i] == 'a')
                    s[i] = 'b';
                else if (s[i] == 'b')
                    s[i] = 'a';
            }
            std::swap(x, y);
        }

        int ans = 0, i = 0;
        while (i < n)
        {
            while (i < n && s[i] != 'a' && s[i] != 'b')
                ++i;

            int ca = 0, cb = 0; // ca:a的数量, cb:b的数量
            while (i < n && (s[i] == 'a' || s[i] == 'b'))
            {
                if (s[i] == 'a')
                {
                    ++ca;
                }
                else    // s[i] == 'b'
                {
                    if (ca > 0) // 删除ab
                    {
                        --ca;
                        ans += x;
                    }
                    else    // 没有a，无法删除ab
                    {
                        ++cb;
                    }
                }
                ++i;
            }

            // 删除ba
            ans += std::min(ca, cb) * y;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
