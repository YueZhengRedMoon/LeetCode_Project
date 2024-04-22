#include <iostream>
#include <vector>

class Sea
{
public:
    bool hasShips(std::vector<int> topRight, std::vector<int> bottomLeft);
};

class Solution
{
public:
    int countShips(Sea sea, std::vector<int> topRight, std::vector<int> bottomLeft)
    {
        return search(sea, bottomLeft[0], bottomLeft[1], topRight[0], topRight[1]);
    }

private:
    int search(Sea& sea, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)
    {
        if (bottomLeftX > topRightX || bottomLeftY > topRightY)
            return 0;
        bool hasShip = sea.hasShips({topRightX, topRightY}, {bottomLeftX, bottomLeftY});
        if (!hasShip)
            return 0;
        if (bottomLeftX == topRightX && bottomLeftY == topRightY)
            return hasShip;

        int midX = (bottomLeftX + topRightX) / 2, midY = (bottomLeftY + topRightY) / 2;
        int res = 0;
        res += search(sea, bottomLeftX, bottomLeftY, midX, midY);       // 左下区域
        res += search(sea, midX + 1, bottomLeftY, topRightX, midY);     // 右下区域
        res += search(sea, bottomLeftX, midY + 1, midX, topRightY);     // 左上区域
        res += search(sea, midX + 1, midY + 1, topRightX, topRightY);   // 右上区域
        return res;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
