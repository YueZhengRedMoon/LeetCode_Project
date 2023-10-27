#include <iostream>
#include <unordered_map>
#include <random>
#include <time.h>

class RandomizedSet
{
public:
    RandomizedSet()
    {
        randomEngine.seed(time(0));
    }

    bool insert(int val)
    {
        if (indices.find(val) == indices.end())
        {
            indices[val] = nums.size();
            nums.push_back(val);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool remove(int val)
    {
        if (indices.find(val) == indices.end())
        {
            return false;
        }
        else
        {
            int valIndex = indices[val];
            indices[nums.back()] = valIndex;
            std::swap(nums[valIndex], nums.back());
            nums.erase(nums.end() - 1);
            indices.erase(val);
            return true;
        }
    }

    int getRandom()
    {
        std::uniform_int_distribution<unsigned int> distribution(0, nums.size() - 1);
        unsigned int randomIndex = distribution(randomEngine);
        return nums[randomIndex];
    }

private:
    std::vector<int> nums;
    std::unordered_map<int, int> indices;
    std::default_random_engine randomEngine;
};


int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}