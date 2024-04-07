#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

class ThroneInheritance
{
public:
    ThroneInheritance(std::string kingName) : king(kingName)
    {
        alive.emplace(king, true);
    }

    void birth(std::string parentName, std::string childName)
    {
        children[parentName].push_back(childName);
        alive.emplace(childName, true);
    }

    void death(std::string name)
    {
        alive[name] = false;
    }

    std::vector<std::string> getInheritanceOrder()
    {
        std::vector<std::string> ans;
        std::function<void(const std::string&)> dfs = [&](const std::string& cur) {
            if (alive[cur])
            {
                ans.push_back(cur);
            }
            for (const auto& child : children[cur])
            {
                dfs(child);
            }
        };
        dfs(king);
        return ans;
    }

private:
    std::unordered_map<std::string, std::vector<std::string>> children;
    std::unordered_map<std::string, bool> alive;
    std::string king;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
