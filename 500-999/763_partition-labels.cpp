#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    std::vector<int> partitionLabels(std::string s)
    {
        // 每个字母的出现区间
        std::unordered_map<char, std::pair<int, int>> unorderedMap;

        // 统计每个字母的出现区间
        for (int i = 0; i < s.size(); ++i)
        {
            auto &partition = unorderedMap[s[i]];
            if (partition.first == 0)
            {
                partition.first = i;
            }
            partition.second = i;
        }
        unorderedMap[s[0]].first = 0;

        // 按照每个字母的首次出现位置排序
        std::vector<std::pair<int, int>> partitions(unorderedMap.size());
        auto it = partitions.begin();
        for (auto mapIt = unorderedMap.begin(); mapIt != unorderedMap.end(); ++mapIt)
        {
            std::cout << "字母" << mapIt->first << "出现的区间：[" << mapIt->second.first << ", " << mapIt->second.second << "]" << std::endl;
            *it = (*mapIt).second;
            ++it;
        }
        std::sort(partitions.begin(), partitions.end());


        int begin = 0, end = partitions[0].second;
        std::vector<int> result;
        for (int i = 1; i < partitions.size(); ++i)
        {
            if (partitions[i].first < end)
            {
                end = std::max(end, partitions[i].second);
            }
            else
            {
                result.push_back(end - begin + 1);
                begin = partitions[i].first;
                end = partitions[i].second;
            }
        }
        result.push_back(end - begin + 1);

        return result;
    }
};

class Solution2
{
public:
    std::vector<int> partitionLabels(std::string s)
    {
        // 每个字符出现的最远位置
        int hash[27] = {0};
        for (int i = 0; i < s.size(); ++i)
        {
            hash[s[i] - 'a'] = i;
        }

        std::vector<int> result;
        int begin = 0, end = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            end = std::max(end, hash[s[i] - 'a']);
            if (i == end)
            {
                result.push_back(end - begin + 1);
                if (i < s.size() - 1)
                {
                    begin = i + 1;
                }
            }
        }

        return result;
    }
};

void printVector(const std::vector<int>& nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    Solution2 solution;
    std::vector<int> result = solution.partitionLabels(std::string("eaaaabaaec"));
    printVector(result);
    return 0;
}