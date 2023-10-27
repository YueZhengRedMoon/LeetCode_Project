#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

class Solution
{
public:
    int minMutation(std::string startGene, std::string endGene, std::vector<std::string> &bank)
    {
        if (startGene == endGene) return 0;
        else if (bank.size() == 0) return -1;

        constexpr int inf = 0x3f3f3f3f;
        std::unordered_map<std::string, int> mutation;
        for (std::string &validGene : bank)
        {
            mutation[validGene] = inf;
        }

        if (mutation.find(endGene) == mutation.end()) return -1;

        const char c[4] = {'A', 'C', 'G', 'T'};
        std::queue<std::string> queue;
        queue.push(startGene);
        mutation[startGene] = 0;
        while (!queue.empty())
        {
            std::string cur = queue.front();
            int curStep = mutation[cur];
            if (cur == endGene)
            {
                return curStep;
            }
            queue.pop();

            ++curStep;
            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (cur[i] != c[j])
                    {
                        std::string next(cur);
                        next[i] = c[j];
                        auto it = mutation.find(next);
                        if (it != mutation.end() && curStep < it->second)
                        {
                            it->second = curStep;
                            queue.push(next);
                        }
                    }
                }
            }
        }

        return -1;
    }
};

class Solution2
{
public:
    int minMutation(std::string startGene, std::string endGene, std::vector<std::string> &bank)
    {
        int n = bank.size();
        std::vector<std::vector<int>> adj(n);
        int endIndex = -1;
        for (int i = 0; i < n; ++i)
        {
            if (endGene == bank[i])
            {
                endIndex = i;
            }
            for (int j = i + 1; j < n; ++j)
            {
                if (valid(bank[i], bank[j]))
                {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        if (endIndex == -1) return -1;

        std::queue<int> queue;
        std::vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i)
        {
            if (valid(startGene, bank[i]))
            {
                queue.push(i);
                visited[i] = true;
            }
        }

        int step = 1;
        while (!queue.empty())
        {
            int queueSize = queue.size();
            for (int i = 0; i < queueSize; ++i)
            {
                int cur = queue.front();
                if (cur == endIndex)
                {
                    return step;
                }
                queue.pop();
                for (int next : adj[cur])
                {
                    if (!visited[next])
                    {
                        visited[next] = true;
                        queue.push(next);
                    }
                }
            }
            ++step;
        }

        return -1;
    }

private:
    const int geneLen{8};

    /** gene1可以通过一次突变变成gene2 */
    bool valid(std::string &gene1, std::string &gene2)
    {
        int diff = 0;
        for (int i = 0; i < geneLen; ++i)
        {
            if (gene1[i] != gene2[i])
            {
                if (++diff > 1)
                {
                    return false;
                }
            }
        }
        return diff == 1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}