#include <iostream>
#include <vector>

class Solution
{
public:
    int minTimeToVisitAllPoints(std::vector<std::vector<int>>& points)
    {
        int ans = 0;
        for (int i = 1; i < points.size(); ++i)
        {
            int x1 = points[i - 1][0], y1 = points[i - 1][1], x2 = points[i][0], y2 = points[i][1];
            ans += std::max(std::abs(x1 - x2), std::abs(y1 - y2));
        }
        return ans;
    }
};

class WrongSolution
{
public:
    int minTimeToVisitAllPoints(std::vector<std::vector<int>>& points)
    {
        // 从(x1,y1)移动到(x2,y2)
        //  - 从(x1,y1)移动到(x2,y1+x2-x1),移动时间为abs(x2-x1),再移动到(x2,y2),移动时间为abs(y2-(y1+x2-x1))=abs(y2-y1-x2+x1)
        //  - 从(x1,y1)移动到(x1+y2-y1,y2),移动时间为abs(y2-y1),再移动到(x2,y2),移动时间为abs(x2-(x1+y2-y1))=abs(x2-x1-y2+y1)
        // 取两者的最小值

        int wrongAns = 0;
        int trueAns = 0;
        for (int i = 1; i < points.size(); ++i)
        {
            int x1 = points[i - 1][0], y1 = points[i - 1][1], x2 = points[i][0], y2 = points[i][1];
            int wrongTime = std::min(std::abs(x2 - x1) + std::abs(y2 - y1 - x2 + x1),
                            std::abs(y2 - y1) + std::abs(x2 - x1 - y2 + y1));
            wrongAns += wrongTime;

           int trueTime = std::max(std::abs(x1 - x2), std::abs(y1 - y2));

           if (wrongTime != trueTime)
           {
               std::cout << "move from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")' s time is incorrect! "
                         << "wrongTime = " << wrongTime << ", trueTime = " << trueTime << std::endl;
               break;
           }
        }
        return wrongAns;
    }
};

int main()
{
    WrongSolution ws;
    std::vector<std::vector<int>> points = {{0, 0}, {1, -1},{559,511},{932,618},{-623,-443},{431,91},{838,-127},{773,-917},
                                            {-500,-910},{830,-417},{-870,73},{-864,-600},{450,535},{-479,-370},
                                            {856,573},{-549,369},{529,-462},{-839,-856},{-515,-447},{652,197},
                                            {-83,345},{-69,423},{310,-737},{78,-201},{443,958},{-311,988},{-477,30},
                                            {-376,-153},{-272,451},{322,-125},{-114,-214},{495,33},{371,-533},
                                            {-393,-224},{-405,-633},{-693,297},{504,210},{-427,-231},{315,27},{991,322},
                                            {811,-746},{252,373},{-737,-867},{-137,130},{507,380},{100,-638},{-296,700},
                                            {341,671},{-944,982},{937,-440},{40,-929},{-334,60},{-722,-92},{-35,-852},
                                            {25,-495},{185,671},{149,-452}};
    int ans = ws.minTimeToVisitAllPoints(points);
    std::cout << ans << std::endl;
    return 0;
}