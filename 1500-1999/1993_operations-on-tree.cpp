#include <iostream>
#include <vector>

class LockingTree
{
public:
    struct Node
    {
        int parent;
        int locker;                 // 当前节点的上锁者，为0表示未上锁
        int childrenLockers;        // 子节点所有上锁者编号的总和
        std::vector<int> children;
    };

    LockingTree(std::vector<int> &parent) : n(parent.size()), nodes(parent.size())
    {
        for (int i = 0; i < n; ++i)
        {
            nodes[i].parent = parent[i];
            if (parent[i] >= 0)
                nodes[parent[i]].children.push_back(i);
        }
    }

    bool lock(int num, int user)
    {
        if (nodes[num].locker == 0)
        {
            nodes[num].locker = user;
            updateChildrenLockers(num, user);
            return true;
        }
        return false;
    }

    bool unlock(int num, int user)
    {
        if (nodes[num].locker == user)
        {
            nodes[num].locker = 0;
            updateChildrenLockers(num, -user);
            return true;
        }
        return false;
    }

    bool upgrade(int num, int user)
    {
        // 指定节点已上锁，或其没有上锁的子孙节点
        if (nodes[num].locker != 0 || nodes[num].childrenLockers == 0)
            return false;

        // 检查其是否有上锁的祖先节点
        int cur = nodes[num].parent;
        while (cur != -1)
        {
            if (nodes[cur].locker != 0)
                return false;
            cur = nodes[cur].parent;
        }

        updateChildrenLockers(num, user - nodes[num].childrenLockers);

        dfsUnlock(num);
        nodes[num].locker = user;

        return true;
    }

private:
    int n;
    std::vector<Node> nodes;

    void updateChildrenLockers(int id, int delta)
    {
        int cur = nodes[id].parent;
        while (cur != -1)
        {
            nodes[cur].childrenLockers += delta;
            cur = nodes[cur].parent;
        }
    }

    void dfsUnlock(int id)
    {
        nodes[id].locker = 0;
        nodes[id].childrenLockers = 0;

        for (int child : nodes[id].children)
        {
            dfsUnlock(child);
        }
    }
};

class LockingTree2
{
public:
    LockingTree2(std::vector<int> &parent)
    {

    }

    bool lock(int num, int user)
    {

    }

    bool unlock(int num, int user)
    {

    }

    bool upgrade(int num, int user)
    {

    }
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
