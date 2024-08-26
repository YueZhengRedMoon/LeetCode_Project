#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

class Employee
{
public:
    int id;
    int importance;
    std::vector<int> subordinates;
};

class Solution
{
public:
    int getImportance(std::vector<Employee*> employees, int id)
    {
        std::unordered_map<int, Employee*> employeeMap;
        employeeMap.reserve(employees.size());
        for (Employee* e : employees)
        {
            employeeMap[e->id] = e;
        }

        std::function<int(Employee*)> dfs = [&](Employee* employee) -> int
        {
            int importance = 0;
            if (employee)
            {
                importance += employee->importance;
                for (int eid : employee->subordinates)
                {
                    importance += dfs(employeeMap[eid]);
                }
            }
            return importance;
        };

        return dfs(employeeMap[id]);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
