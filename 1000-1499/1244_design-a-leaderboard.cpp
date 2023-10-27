#include <iostream>
#include <list>
#include <unordered_map>

class Leaderboard
{
public:
    Leaderboard() {}

    void addScore(int playerId, int score)
    {
        auto mapIt = iterMap.find(playerId);
        if (mapIt == iterMap.end())
        {
            std::list<int>::iterator iter = scores.begin();
            while (iter != scores.end() && *iter > score)
            {
                ++iter;
            }
            iterMap[playerId] = scores.emplace(iter, score);
        }
        else
        {
            std::list<int>::iterator iter = mapIt->second;
            *iter += score;
            if (iter == scores.begin())
                return;

            std::list<int>::iterator it;
            for (it = scores.begin(); it != iter && *it > *iter; ++it);
            if (it != iter)
            {
                scores.splice(it, scores, iter);
            }
        }
    }

    int top(int k)
    {
        int sum = 0;
        std::list<int>::iterator iter = scores.begin();
        for (int i = 0; i < k; ++i, ++iter)
        {
            sum += *iter;
        }
        return sum;
    }

    void reset(int playerId)
    {
        std::list<int>::iterator iter = iterMap[playerId];
        scores.erase(iter);
        iterMap.erase(playerId);
    }

private:
    std::list<int> scores;  // 分数，从大到小排序
    std::unordered_map<int, std::list<int>::iterator> iterMap;
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}