#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> decrypt(std::vector<int>& code, int k)
    {
        int n = code.size();
        if (k == 0)
        {
            return std::vector<int>(n, 0);
        }

        // prefix[i] = sum(code[0, i))
        std::vector<int> prefix(2 * n + 1, 0);
        for (int i = 1; i <= 2 * n; ++i)
        {
            prefix[i] = prefix[i - 1] + code[(i - 1) % n];
        }

        if (k > 0)
        {
            for (int i = 0; i < n; ++i)
            {
                code[i] = prefix[i + k + 1] - prefix[i + 1];
            }
        }
        else
        {
            for (int i = n; i < 2 * n; ++i)
            {
                code[i - n] = prefix[i] - prefix[i + k];
            }
        }

        return code;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
