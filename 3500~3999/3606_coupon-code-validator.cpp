#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>

class Solution
{
public:
    std::vector<std::string> validateCoupons(std::vector<std::string>& code,
                                             std::vector<std::string>& businessLine, std::vector<bool>& isActive)
    {
        int n = code.size();
        std::vector<int> indices;
        for (int i = 0; i < n; ++i)
        {
            if (isActive[i] && isValidCode(code[i]) && isValidBusiness(businessLine[i]))
                indices.push_back(i);
        }
        if (indices.empty())
            return {};

        std::sort(indices.begin(), indices.end(),
                  [&](int i, int j) {
            if (businessLine[i] == businessLine[j])
                return code[i] < code[j];
            else
                return businessLine[i] < businessLine[j];
        });

        std::vector<std::string> ans;
        ans.reserve(indices.size());
        for (int idx : indices)
        {
            ans.push_back(code[idx]);
        }
        return ans;
    }

private:
    bool isValidCode(std::string_view code)
    {
        if (code.empty())
            return false;

        for (char c : code)
        {
            if (!(std::isalpha(c) || std::isdigit(c) || c == '_'))
                return false;
        }
        return true;
    }

    bool isValidBusiness(std::string_view businessLine)
    {
        return  businessLine == "electronics" || businessLine == "grocery" ||
                businessLine == "pharmacy" || businessLine == "restaurant";
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}