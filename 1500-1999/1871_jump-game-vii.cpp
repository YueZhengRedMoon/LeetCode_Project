#include <iostream>
#include <vector>

class Solution
{
public:
    bool canReach(std::string s, int minJump, int maxJump)
    {
        if (s.back() != '0')
        {
            return false;
        }

        int n = s.size();
        std::vector<int> diff(n + 1, 0);
        ++diff[minJump];
        --diff[maxJump + 1];
        int reachable = 0;
        for (int i = 1; i < n; ++i)
        {
            reachable += diff[i];
            if (reachable && s[i] == '0')
            {
                if (i + minJump < n)
                {
                    ++diff[i + minJump];
                    --diff[std::min(i + maxJump + 1, n)];
                }
            }
        }
        return reachable;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}