#include <iostream>
#include <vector>

class Solution
{
public:
    int totalFruit(std::vector<int>& fruits)
    {
        int ans = 0;
        std::pair<int, int> basket1(-1, 0), basket2(-1, 0); // first:水果的种类，-1表示没有水果 second:水果的数量
        for (int i = 0, j = 0; j < fruits.size(); ++j)
        {
            int x = fruits[j];

            while (basket1.first != -1 && basket2.first != -1 && basket1.first != x && basket2.first != x)
            {
                int y = fruits[i++];
                if (y == basket1.first)
                {
                    if (--basket1.second == 0)
                        basket1.first = -1;
                }
                else    // y == basket2.first
                {
                    if (--basket2.second == 0)
                        basket2.first = -1;
                }
            }

            if (x == basket1.first)
            {
                ++basket1.second;
            }
            else if (x == basket2.first)
            {
                ++basket2.second;
            }
            else if (basket1.first == -1)
            {
                basket1.first = x;
                basket1.second = 1;
            }
            else    // basket2.first == -1
            {
                basket2.first = x;
                basket2.second = 1;
            }

            ans = std::max(ans, j - i + 1);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
