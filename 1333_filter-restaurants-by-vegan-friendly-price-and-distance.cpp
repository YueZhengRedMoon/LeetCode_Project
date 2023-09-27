#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> filterRestaurants(std::vector<std::vector<int>> &restaurants,
                                       int veganFriendly, int maxPrice, int maxDistance)
    {
        int n = restaurants.size();
        std::vector<int> ans;
        for (int i = 0; i < n; ++i)
        {
            int vegan = restaurants[i][2], price = restaurants[i][3], distance = restaurants[i][4];
            if ((!veganFriendly || vegan) && price <= maxPrice && distance <= maxDistance)
                ans.push_back(i);
        }
        std::sort(ans.begin(), ans.end(), [&](int lhs, int rhs){
            int id1 = restaurants[lhs][0], id2 = restaurants[rhs][0];
            int rating1 = restaurants[lhs][1], rating2 = restaurants[rhs][1];
            return rating1 == rating2 ? id1 > id2 : rating1 > rating2;
        });
        for (int &id : ans)
            id = restaurants[id][0];
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
