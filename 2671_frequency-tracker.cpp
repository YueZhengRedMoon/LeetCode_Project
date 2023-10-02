#include <iostream>
#include <cstring>
#include <unordered_map>

class FrequencyTracker
{
public:
    FrequencyTracker()
    {
        std::memset(count, 0, sizeof(count));
    }

    void add(int number)
    {
        auto &ref = frequency[count[number]];
        if (ref > 0)
        {
            --ref;
        }
        ++count[number];
        ++frequency[count[number]];
    }

    void deleteOne(int number)
    {
        if (count[number] > 0)
        {
            --frequency[count[number]];
            --count[number];
            ++frequency[count[number]];
        }
    }

    bool hasFrequency(int targetFrequency)
    {
        return frequency[targetFrequency] > 0;
    }

private:
    /** 存储每个数出现的次数 */
    int count[100001];

    /** 存储每个频率出现的次数 */
    std::unordered_map<int, int> frequency;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
