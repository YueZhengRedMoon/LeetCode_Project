#include <iostream>
#include <memory>

class WordDictionary
{
public:
    WordDictionary()
    {

    }

    void addWord(std::string word)
    {
        addWord(word, 0);
    }

    bool search(std::string word)
    {
        return search(word, 0);
    }

private:
    std::shared_ptr<WordDictionary> children[26]{nullptr};
    bool isEnd{false};

    void addWord(const std::string &word, int begin)
    {
        int index = word[begin] - 'a';
        if (children[index] == nullptr)
        {
            children[index] = std::make_shared<WordDictionary>();
        }
        int len = word.size();
        if (begin == len - 1)
        {
            children[index]->isEnd = true;
        }
        else
        {
            children[index]->addWord(word, begin + 1);
        }
    }

    bool search(const std::string &word, int begin)
    {
        int len = word.size();
        if (word[begin] == '.')
        {
            if (begin == len - 1)
            {
                for (int i = 0; i < 26; ++i)
                {
                    if (children[i] != nullptr && children[i]->isEnd)
                    {
                        return true;
                    }
                }
            }
            else
            {
                for (int i = 0; i < 26; ++i)
                {
                    if (children[i] != nullptr && children[i]->search(word, begin + 1))
                    {
                        return true;
                    }
                }
            }
        }
        else
        {
            int index = word[begin] - 'a';
            if (begin == len - 1)
            {
                return children[index] != nullptr && children[index]->isEnd;
            }
            if (children[index] != nullptr)
            {
                return children[index] != nullptr && children[index]->search(word, begin + 1);
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
