#include <iostream>
#include <vector>
#include <memory>
#include <string_view>

constexpr int MAX_ALPHABET = 26;

struct Node
{
    int endIdx{-1}; // 该节点是哪个字符串的结束节点，=-1表示不是结束节点
    int shortestIdx{-1};    // 该节点是哪个最短最早字符串的后缀，=-1表示还不确定
    std::shared_ptr<Node> children[MAX_ALPHABET]{nullptr};

    int getShortestIdx(const std::vector<std::string>& wordsContainer)
    {
        if (shortestIdx != -1)
        {
            return shortestIdx;
        }
        if (endIdx != -1)
        {
            shortestIdx = endIdx;
            return shortestIdx;
        }
        for (int i = 0; i < MAX_ALPHABET; ++i)
        {
            if (children[i])
            {
                int j = children[i]->getShortestIdx(wordsContainer);
                if (shortestIdx == -1 || wordsContainer[j].size() < wordsContainer[shortestIdx].size() ||
                    (wordsContainer[j].size() == wordsContainer[shortestIdx].size() && j < shortestIdx))
                {
                    shortestIdx = j;
                }
            }
        }
        return shortestIdx;
    }
};

class Solution
{
public:
    std::vector<int> stringIndices(std::vector<std::string>& wordsContainer, std::vector<std::string>& wordsQuery)
    {
        std::shared_ptr<Node> root = std::make_shared<Node>();
        int minLen = INT_MAX, shortestStrIdx = -1;
        for (int i = 0; i < wordsContainer.size(); ++i)
        {
            std::string_view s = wordsContainer[i];
            if (s.size() < minLen)
            {
                minLen = s.size();
                shortestStrIdx = i;
            }

            std::shared_ptr<Node> p = root;
            for (int j = (int) s.size() - 1; j >= 0; --j)
            {
                int idx = s[j] - 'a';
                if (p->children[idx] == nullptr)
                {
                    p->children[idx] = std::make_shared<Node>();
                }
                p = p->children[idx];
            }
            if (p->endIdx == -1)
            {
                p->endIdx = i;
            }
        }

        std::vector<int> ans(wordsQuery.size());
        for (int i = 0; i < wordsQuery.size(); ++i)
        {
            int len = wordsQuery[i].size();
            if (root->children[wordsQuery[i][len - 1] - 'a'] == nullptr)
            {
                ans[i] = shortestStrIdx;
                continue;
            }

            std::shared_ptr<Node> p = root;
            for (int j = len - 1; j >= 0; --j)
            {
                int idx = wordsQuery[i][j] - 'a';
                if (p->children[idx] == nullptr)
                {
                    break;
                }
                else
                {
                    p = p->children[idx];
                }
            }
            ans[i] = p->getShortestIdx(wordsContainer);
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::string> wordsContainer = {"abcd","bcd","xbcd"};
    std::vector<std::string> wordsQuery = {"cd","bcd","xyz"};
    std::vector<int> ans = solution.stringIndices(wordsContainer, wordsQuery);
    for (int x : ans)
    {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    return 0;
}