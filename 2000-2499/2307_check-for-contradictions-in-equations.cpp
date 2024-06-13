#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <unordered_set>

class Solution
{
public:
    bool checkContradictions(std::vector<std::vector<std::string>>& equations, std::vector<double>& values)
    {
        int n = equations.size();
        std::unordered_map<std::string, std::unordered_map<std::string, double>> g;
        for (int i = 0; i < n; ++i)
        {
            const std::string &a = equations[i][0], &b = equations[i][1];
            double v = values[i];
            if (a != b)
            {
                if (g.find(a) == g.end() || g[a].find(b) == g[a].end())
                {
                    g[a].emplace(b, v);
                    g[b].emplace(a, 1.0 / v);
                }
                else if (!equal(g[a][b], v))
                {
                    return true;
                }
            }
            else
            {
                if (!equal(values[i], 1.0))
                    return true;
            }
        }

        std::unordered_set<std::string> visited;
        double targetValue;
        std::function<bool(const std::string&, const std::string&, double)>
        dfs = [&](const std::string& a, const std::string& target, double val) -> bool {
            if (a == target)
            {
                return equal(val, targetValue);
            }
            visited.insert(a);
            for (const auto& [b, v] : g[a])
            {
                if (visited.find(b) == visited.end())
                {
                    if (!dfs(b, target, val * v))
                        return false;
                }
            }
            visited.erase(a);
            return true;
        };

        for (int i = 0; i < n; ++i)
        {
            targetValue = values[i];
            const std::string &a = equations[i][0], &b = equations[i][1];
            if (!dfs(a, b, 1.0))
                return true;
        }
        return false;
    }

private:
    bool equal(double a, double b)
    {
        return std::abs(a - b) < 1e-5;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<std::string>> equations = {{"le", "et"}, {"le", "code"}, {"code", "et"}};
    std::vector<double> values = {2, 5, 0.5};
    bool ans = solution.checkContradictions(equations, values);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}
