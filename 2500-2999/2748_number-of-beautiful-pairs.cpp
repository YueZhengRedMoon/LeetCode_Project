#include <iostream>
#include <vector>

class Solution
{
public:
    int countBeautifulPairs(std::vector<int>& nums)
    {
        int ans = 0;
        int counter[10]{0};
        for (int x : nums)
        {
            int last = x % 10;
            while (x >= 10)
                x /= 10;
            int first = x;

            switch (last)
            {
                case 1:
                    for (int i = 1; i <= 9; ++i)
                        ans += counter[i];
                    break;
                case 2:
                    ans += counter[1] + counter[3] + counter[5] + counter[7] + counter[9];
                    break;
                case 3:
                    ans += counter[1] + counter[2] + counter[4] + counter[5] + counter[7] + counter[8];
                    break;
                case 4:
                    ans += counter[1] + counter[3] + counter[5] + counter[7] + counter[9];
                    break;
                case 5:
                    ans += counter[1] + counter[2] + counter[3] + counter[4] + counter[6] + counter[7] + counter[8] + counter[9];
                    break;
                case 6:
                    ans += counter[1] + counter[5] + counter[7];
                    break;
                case 7:
                    ans += counter[1] + counter[2] + counter[3] + counter[4] + counter[5] + counter[6] + counter[8] + counter[9];
                    break;
                case 8:
                    ans += counter[1] + counter[3] + counter[5] + counter[7] + counter[9];
                    break;
                case 9:
                    ans += counter[1] + counter[2] + counter[4] + counter[5] + counter[7] + counter[8];
                    break;
            }
            ++counter[first];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
