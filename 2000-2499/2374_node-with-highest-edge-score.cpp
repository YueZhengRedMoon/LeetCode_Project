#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int edgeScore(std::vector<int>& edges)
    {
        int n = edges.size();
        std::vector<long long> score(n, 0);
        for (int i = 0; i < n; ++i)
        {
            score[edges[i]] += i;
        }
        return std::max_element(score.begin(), score.end()) - score.begin();
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
