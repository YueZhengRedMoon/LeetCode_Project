#include <iostream>
#include <list>
#include <vector>

class Solution
{
public:
    int minNumberOfFrogs(std::string croakOfFrogs)
    {
        std::list<int> croakList[5];
        for (int i = 0; i < croakOfFrogs.size(); ++i)
        {
            croakList[hash(croakOfFrogs[i])].push_back(i);
        }

        if (!(croakList[0].size() == croakList[1].size() && croakList[1].size() == croakList[2].size()
            && croakList[2].size() == croakList[3].size() && croakList[3].size() == croakList[4].size()))
        {
            return -1;
        }

        std::vector<std::pair<int, int>> interval;  // 青蛙叫声的区间
        while (!croakList[0].empty() && !croakList[1].empty() && !croakList[2].empty()
                && !croakList[3].empty() && !croakList[4].empty())
        {
            int begin = croakList[0].front();
            croakList[0].pop_front();
            int end = begin;
            for (int i = 1; i < 5; ++i)
            {
                int current = croakList[i].front();
                if (current < end)
                {
                    return -1;
                }
                end = current;
                croakList[i].pop_front();
            }
            interval.emplace_back(begin, end);
        }

        for (int i = 0; i < 5; ++i)
        {
            if (!croakList[i].empty())
                return -1;
        }

        // 统计最多有多少个重叠区间
        int result = 1;
        int overlap = 1;
        int start = 0;
        for (int i = 1; i < interval.size(); ++i)
        {
            while (i != start && interval[i].first > interval[start].second)
            {
                ++start;
                --overlap;
            }
            if (i != start)
            {
                ++overlap;
            }
            else
            {
                overlap = 1;
            }
            if (overlap > result)
                result = overlap;
        }

        return result;
    }

private:
    inline int hash(char c)
    {
        switch (c)
        {
            case 'c':
                return 0;
            case 'r':
                return 1;
            case 'o':
                return 2;
            case 'a':
                return 3;
            case 'k':
                return 4;
        }
        return -1;
    }
};

class Solution2
{
public:
    int minNumberOfFrogs(std::string croakOfFrogs)
    {
        // 预处理每个字母在"croak"中的上一个字母
        char previous['s']; // 's'保证"croak"中的任意字符都不会越界
        const std::string croak("croakc");
        for (int i = 1; i < croak.size(); ++i)
        {
            previous[croak[i]] = croak[i - 1];
        }

        int cnt['s']{0};
        for (char ch : croakOfFrogs)
        {
            char pre = previous[ch];
            if (cnt[pre])   // 如果有青蛙发出了pre的声音
                --cnt[pre]; // 复用一只
            else if (ch != 'c') // 没有青蛙发出pre的声音，且此次发声不是从'c'开始
                return -1;
            ++cnt[ch];  // 发出了ch的声音
        }

        if (cnt['c'] || cnt['r'] || cnt['o'] || cnt['a'])
            return -1;
        return cnt['k'];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}