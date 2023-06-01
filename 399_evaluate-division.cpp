#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "debug.h"

class Solution
{
public:
    using Divide = std::unordered_map<std::string, std::unordered_map<std::string, double>>;

    std::vector<double> calcEquation(std::vector<std::vector<std::string>> &equations,
                                     std::vector<double> &values,
                                     std::vector<std::vector<std::string>> &queries)
    {

        Divide divide;
        std::unordered_set<std::string> variables;
        std::unordered_map<std::string, bool> visited;
        for (int i = 0; i < equations.size(); ++i)
        {
            divide[equations[i][0]][equations[i][1]] = values[i];
            divide[equations[i][1]][equations[i][0]] = 1.0 / values[i];
            variables.insert({equations[i][0], equations[i][1]});
        }

        std::vector<double> ans;
        ans.reserve(queries.size());
        for (const auto &query : queries)
        {
            const std::string &numerator = query[0];
            const std::string &denominator = query[1];
            if (variables.find(numerator) == variables.end()
            || variables.find(denominator) == variables.end())
            {
                ans.push_back(-1.0);
            }
            else if (numerator == denominator)
            {
                ans.push_back(1.0);
            }
            else
            {
                for (auto it = visited.begin(); it != visited.end(); ++it)
                {
                    it->second = false;
                }
                double res = dfs(divide, visited, numerator, denominator);
                if (res != -1.0)
                {
                    divide[numerator][denominator] = res;
                    divide[denominator][numerator] = 1.0 / res;
                }
                ans.push_back(res);
                for (auto it1 = divide.begin(); it1 != divide.end(); ++it1)
                {
                    for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
                    {
                        std::cout << it1->first << " / " << it2->first << " = " << it2->second << std::endl;
                    }
                }
                std::cout << std::endl;
            }
        }

        return ans;
    }

private:
    double dfs(Divide &divide, std::unordered_map<std::string, bool> &visited,
               const std::string &numerator, const std::string &denominator)
    {
        auto it1 = divide.find(numerator);
        if (it1 == divide.end())
        {
            return -1.0;
        }
        visited[numerator] = true;
        auto it2 = it1->second.find(denominator);
        if (it2 != it1->second.end())
        {
            return it2->second;
        }
        for (auto [newNumerator, value] : it1->second)
        {
            if (visited[newNumerator])
            {
                continue;
            }
            double res = dfs(divide, visited, newNumerator, denominator);
            if (res != -1.0)
            {
                divide[newNumerator][denominator] = res;
                divide[denominator][newNumerator] = 1.0 / res;
                res *= value;
                it1->second[denominator] = value * res;
                divide[denominator][numerator] = 1.0 / res;
                return res;
            }
        }
        return -1.0;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<std::string>> equations = {{"x1", "x2"}, {"x2", "x3"}, {"x3", "x4"}, {"x4", "x5"}};
    std::vector<double> values = {3.0, 4.0, 5.0, 6.0};
    std::vector<std::vector<std::string>> queries = {{"x1", "x5"}, {"x5", "x2"}, {"x2", "x4"}, {"x2", "x2"}};
    std::vector<double> ans = solution.calcEquation(equations, values, queries);
    debug::printVector(ans);
    return 0;
}
