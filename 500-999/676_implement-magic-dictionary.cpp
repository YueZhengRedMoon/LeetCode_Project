#include <iostream>
#include <vector>
#include <memory>
#include <string_view>

struct Node
{
    bool isEnd{false};
    std::shared_ptr<Node> children[26];
};

class MagicDictionary
{
public:
    MagicDictionary() : root(std::make_shared<Node>()) {}

    void buildDict(std::vector<std::string> dictionary)
    {
        for (std::string_view word : dictionary)
        {
            std::shared_ptr<Node> cur = root;
            for (char c : word)
            {
                int cIdx = getIndex(c);
                if (cur->children[cIdx] == nullptr)
                {
                    cur->children[cIdx] = std::make_shared<Node>();
                }
                cur = cur->children[cIdx];
            }
            cur->isEnd = true;
        }
    }

    bool search(std::string searchWord)
    {
        return search(searchWord, 0, false, root);
    }

private:
    std::shared_ptr<Node> root;

    int getIndex(char c)
    {
        return c - 'a';
    }

    bool search(std::string_view searchWord, int i, bool isReplaced, std::shared_ptr<Node> node)
    {
        if (i == searchWord.size())
        {
            return isReplaced && node->isEnd;
        }

        int cIdx = getIndex(searchWord[i]);
        if (isReplaced)
        {
            return node->children[cIdx] && search(searchWord, i + 1, isReplaced, node->children[cIdx]);
        }
        else    // isReplaced == false
        {
            for (int j = 0; j < 26; ++j)
            {
                if (node->children[j] == nullptr)
                    continue;

                if (search(searchWord, i + 1, j != cIdx, node->children[j]))
                    return true;
            }
        }

        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
