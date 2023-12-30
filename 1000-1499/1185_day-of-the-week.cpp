#include <iostream>
#include <ctime>
#include <vector>

class Solution
{
public:
    Solution() : week({"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}) {}

    std::string dayOfTheWeek(int day, int month, int year)
    {
        // 获取当前系统的时间
        std::time_t t = std::time(0);
        std::tm *now = std::localtime(&t);

        // 设置年月日
        now->tm_year = year - 1900;
        now->tm_mon = month - 1;
        now->tm_mday = day;

        // 计算星期几
        std::mktime(now);

        // 获得星期几
        int dayOfWeek = now->tm_wday;
        return week[dayOfWeek];
    }

private:
    std::vector<std::string> week;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
