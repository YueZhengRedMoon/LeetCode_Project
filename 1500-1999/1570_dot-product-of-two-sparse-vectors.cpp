#include <iostream>
#include <vector>
#include <unordered_map>

class SparseVector
{
public:
    SparseVector(std::vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i])
                values[i] = nums[i];
        }
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec)
    {
        int ans = 0;
        for (auto [idx, val] : values)
        {
            auto it = vec.values.find(idx);
            if (it != vec.values.end())
            {
                ans += val * it->second;
            }
        }
        return ans;
    }

private:
    std::unordered_map<int, int> values;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
