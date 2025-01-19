#include <iostream>
#include <string>

class Solution
{
public:
    int countTexts(std::string pressedKeys)
    {
        const int MOD = 1'000'000'007;
        int f[5] = {1, 0, 0, 0, 0};    // f[i]:pressedKeys[0, i)可能有多少种文字信息, f[0] = 1
        int len = pressedKeys.size();
        for (int i = 0; i < len; ++i)
        {
            int cur = (i + 1) % 5;
            f[cur] = f[i % 5];  // xxxxy
            if (i >= 1 && pressedKeys[i] == pressedKeys[i - 1])  // xxxyy
            {
                f[cur] = (f[cur] + f[(i - 1) % 5]) % MOD;
                if (i >= 2 && pressedKeys[i] == pressedKeys[i - 2]) // xxyyy
                {
                    f[cur] = (f[cur] + f[(i - 2) % 5]) % MOD;
                    if ((pressedKeys[i] == '7' || pressedKeys[i] == '9') && i >= 3 && pressedKeys[i] == pressedKeys[i - 3]) // xyyyy
                    {
                        f[cur] = (f[cur] + f[(i - 3) % 5]) % MOD;
                    }
                }
            }
        }
        return f[len % 5];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
