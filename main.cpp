#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

struct Person
{
    std::string name;
    int age;
};

class PersonAgeLess
{
public:
    // 大顶堆优先队列比较函数
    bool operator()(const Person &lhs, const Person &rhs) const
    {
        return lhs.age < rhs.age;
    }
};

class PersonAgeGreater
{
public:
    // 小顶堆优先队列比较函数
    bool operator()(const Person &lhs, const Person &rhs) const
    {
        return lhs.age > rhs.age;
    }
};

void printVector(std::vector<int>& nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<Person> persons = {{"Alice", 19}, {"Dorothy", 18}, {"Lili", 28}};
    std::make_heap(persons.begin(), persons.end(), PersonAgeLess());
    Person kirie = {"Kirie", 300};
    persons.push_back(kirie);
    std::push_heap(persons.begin(), persons.end(), PersonAgeLess());
    std::cout << "加入堆后" << std::endl;
    for (const auto& person : persons)
    {
        std::cout << person.name << "(" << person.age << ") ";
    }
    std::cout << std::endl;

    std::pop_heap(persons.begin(), persons.end(), PersonAgeLess());
    Person top = persons.back();
    std::cout << "top.name = " << top.name << ", top.age = " << top.age << std::endl;
    std::cout << "弹出堆后" << std::endl;
    for (const auto& person : persons)
    {
        std::cout << person.name << "(" << person.age << ") ";
    }
    std::cout << std::endl;

    std::vector<int> vec{3, 2, 1, 5, 6, 4};
    std::make_heap(vec.begin(), vec.end(), std::less<int>());   // 大顶堆

    std::cout << "大顶堆的元素：";
    printVector(vec);

    std::cout << "小顶堆的元素：";
    std::make_heap(vec.begin(), vec.end(), std::greater<int>());    // 小顶堆
    printVector(vec);

    std::priority_queue<Person, std::vector<Person>, PersonAgeGreater> priorityQueue;
    priorityQueue.push({"Alice", 19});
    priorityQueue.push({"Dorothy", 18});
    priorityQueue.push({"Lili", 28});

    std::cout << "优先队列中的元素：\n";
    while (!priorityQueue.empty())
    {
        std::cout << priorityQueue.top().name << " (" << priorityQueue.top().age << ")\n";
        priorityQueue.pop();
    }
    std::priority_queue<int, std::vector<int>, std::greater<int> > intPriorityQueue;
    intPriorityQueue.push(5);
    intPriorityQueue.push(4);
    intPriorityQueue.push(1);
    intPriorityQueue.push(3);
    intPriorityQueue.push(2);
    std::vector<int> intVec;
    while (!intPriorityQueue.empty())
    {
        intVec.push_back(intPriorityQueue.top());
        intPriorityQueue.pop();
    }
    std::cout << "内置类型优先队列指定std::greater为排序函数排序结果：";
    printVector(intVec);
    return 0;
}
