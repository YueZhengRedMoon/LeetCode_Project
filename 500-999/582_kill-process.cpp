#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

class Solution
{
public:
    std::vector<int> killProcess(std::vector<int> &pids, std::vector<int> &ppids, int kill)
    {
        int n = pids.size();
        std::unordered_map<int, int> pidIndex;
        pidIndex.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            pidIndex[pids[i]] = i;
        }

        std::function<int(int)> getParent = [&](int pid) {
            int index = pidIndex[pid];
            if (ppids[index] == 0 || ppids[index] == kill)
                return ppids[index];
            return ppids[index] = getParent(ppids[index]);
        };

        std::vector<int> ans;
        for (int i = 0; i < n; ++i)
        {
            if (pids[i] == kill || getParent(pids[i]) == kill)
            {
                ans.push_back(pids[i]);
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
