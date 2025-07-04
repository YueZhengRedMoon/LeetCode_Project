#include <iostream>
#include <vector>

class Solution
{
public:
    char kthCharacter(long long k, std::vector<int>& operations)
    {
        std::vector<int> opStack;
        while (k > 1)
        {
            int x = findExponent(k);
            opStack.push_back(operations[x - 1]);
            k -= (1ll << (x - 1));
        }

        char ans = 'a';
        for (auto it = opStack.crbegin(); it != opStack.crend(); ++it)
        {
            int op = *it;
            ans += op;
            if (ans > 'z')
                ans = 'a';
        }

        return ans;
    }

private:
    // 找到指数x,使得 2^x >= k
    int findExponent(long long k)
    {
        int x = 0;
        long long t = 1;
        while (t < k)
        {
            t <<= 1;
            ++x;
        }
        return x;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
