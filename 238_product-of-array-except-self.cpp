#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> productExceptSelf(std::vector<int> &nums)
    {
        std::vector<int> answer(nums.size(), 0);
        int product = 1;
        int zeroCount = 0;
        for (int num : nums)
        {
            if (num == 0)
            {
                if (++zeroCount >= 2)
                {
                    return answer;
                }
            }
            else
            {
                product *= num;
            }
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i])
            {
                answer[i] = zeroCount ? 0 : product / nums[i];
            }
            else
            {
                answer[i] = product;
            }
        }

        return answer;
    }
};

class Solution2
{
public:
    std::vector<int> productExceptSelf(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<int> answer(n, 1);
        int prefixProduct = 1, suffixProduct = 1;
        for (int i = 0, j = n - 1; i < n; ++i, --j)
        {
            answer[i] *= prefixProduct;
            answer[j] *= suffixProduct;
            prefixProduct *= nums[i];
            suffixProduct *= nums[j];
        }
        return answer;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
