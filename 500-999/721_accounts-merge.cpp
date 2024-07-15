#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string_view>
#include <algorithm>
#include <functional>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>> &accounts)
    {
        // 建图
        // key:邮箱地址 value:邮箱所属账户
        std::unordered_map<std::string_view, std::string_view> owner;
        // key:邮箱地址 value:同一账户下的其它邮箱地址
        std::unordered_map<std::string_view, std::vector<std::string_view>> g;

        for (const std::vector<std::string>& account : accounts)
        {
            std::string_view userName = account.front();
            int size = account.size();
            for (int i = 1; i < size; ++i)
            {
                std::string_view e1 = account[i];
                owner[e1] = userName;
                g.emplace(e1, std::vector<std::string_view>());

                for (int j = i + 1; j < size; ++j)
                {
                    std::string_view e2 = account[j];
                    g[e1].emplace_back(e2);
                    g[e2].emplace_back(e1);
                }
            }
        }

        std::vector<std::vector<std::string>> ans;
        std::unordered_set<std::string_view> visited;
        std::function<void(std::string_view, std::vector<std::string>&)>
        dfs = [&](std::string_view x, std::vector<std::string>& account)
        {
            account.emplace_back(x);
            visited.emplace(x);
            for (std::string_view y : g[x])
            {
                if (visited.find(y) == visited.end())
                    dfs(y, account);
            }
        };
        for (auto it = g.begin(); it != g.end(); ++it)
        {
            std::string_view x = it->first;
            if (visited.find(x) != visited.end())
                continue;

            ans.emplace_back();
            std::vector<std::string>& account = ans.back();
            account.emplace_back(owner[x]);
            dfs(x, account);
            std::sort(account.begin() + 1, account.end());
        }
        return ans;
    }
};

namespace WrongAnswer
{
    class Solution
    {
    public:
        std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>>& accounts)
        {
            std::unordered_multimap<std::string_view, std::unordered_set<std::string_view>> accountsMap;
            for (const std::vector<std::string>& account : accounts)
            {
                std::string_view user = account[0];
                auto it = accountsMap.find(user);
                bool isExist = false; // 该用户是否已经存在
                while (it != accountsMap.end() && it->first == user && !isExist)
                {
                    std::unordered_set<std::string_view>& emailSet = it->second;
                    for (auto emailIt = account.begin() + 1; emailIt != account.end(); ++emailIt)
                    {
                        if (emailSet.find(*emailIt) != emailSet.end())
                        {
                            for (auto eit = account.begin() + 1; eit != account.end(); ++eit)
                                emailSet.insert(*eit);
                            isExist = true;
                            break;
                        }
                    }
                    ++it;
                }
                if (!isExist)
                {
                    accountsMap.emplace(user, std::unordered_set<std::string_view>(account.begin() + 1, account.end()));
                }
            }

            std::vector<std::vector<std::string>> ans;
            ans.reserve(accountsMap.size());
            for (auto it = accountsMap.begin(); it != accountsMap.end(); ++it)
            {
                std::string_view user = it->first;
                std::unordered_set<std::string_view>& emailSet = it->second;

                ans.emplace_back(std::vector<std::string>());
                std::vector<std::string>& account = ans.back();
                account.reserve(emailSet.size() + 1);
                account.emplace_back(user);
                account.insert(account.end(), emailSet.begin(), emailSet.end());
                std::sort(account.begin(), account.end());
            }

            return ans;
        }
    };
}

int main()
{
    Solution solution;
    std::vector<std::vector<std::string>> accounts = {{"John","johnsmith@mail.com","john_newyork@mail.com"},
                                                      {"John","johnsmith@mail.com","john00@mail.com"},
                                                      {"Mary","mary@mail.com"},
                                                      {"John","johnnybravo@mail.com"}};
    std::vector<std::vector<std::string>> ans = solution.accountsMerge(accounts);
    debug::printVector2D(ans);
    return 0;
}
