#include <iostream>
#include <string>

class Solution
{
public:
    std::string getHint(std::string secret, std::string guess)
    {
        int n = secret.size();
        int cnt[10]{0};
        for (int i = 0; i < n; ++i)
        {
            cnt[secret[i] - '0'] += (secret[i] != guess[i]);
        }

        int x = 0, y = 0;
        for (int i = 0; i < n; ++i)
        {
            if (secret[i] == guess[i])
            {
                ++x;
            }
            else
            {
                y += cnt[guess[i] - '0']-- > 0;
            }
        }

        return std::to_string(x) + "A" + std::to_string(y) + "B";
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
