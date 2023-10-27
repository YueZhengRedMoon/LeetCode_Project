#include <iostream>
#include <vector>
#include <unordered_set>

class HtmlParser
{
public:
    std::vector<std::string> getUrls(std::string url);
};

class Solution
{
public:
    std::vector<std::string> crawl(std::string url, HtmlParser htmlParser)
    {
        startUrl = url;
        startUrlLen = startUrl.size();

        dfs(startUrl, htmlParser);

        ans.push_back(startUrl);
        return ans;
    }

private:
    std::vector<std::string> ans;
    std::unordered_set<std::string> visited;
    std::string startUrl;
    int startUrlLen;

    void dfs(const std::string &curUrl, HtmlParser &htmlParser)
    {
        visited.emplace(curUrl);
        std::vector<std::string> urls = htmlParser.getUrls(curUrl);
        for (const std::string &url : urls)
        {
            if (visited.find(url) == visited.end())
            {
                if (isSameHostName(url))
                {
                    ans.push_back(url);
                    dfs(url, htmlParser);
                }
            }
        }
    }

    bool isSameHostName(const std::string &url)
    {
        int i, urlLen = url.size();
        for (i = 7; i < startUrlLen && i < urlLen && url[i] != '/'; ++i)
        {
            if (url[i] != startUrl[i])
                return false;
        }
        return i == urlLen || url[i] == '/';
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}