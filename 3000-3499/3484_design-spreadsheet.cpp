#include <iostream>
#include <string>
#include <vector>
#include "../debug/debug.h"

class Spreadsheet
{
public:
    Spreadsheet(int rows) : sheet(rows, std::vector<int>(26, 0)) {}

    void setCell(std::string cell, int value)
    {
        auto [i, j] = getCellIndex(cell);
        sheet[i][j] = value;
    }

    void resetCell(std::string cell)
    {
        auto [i, j] = getCellIndex(cell);
        sheet[i][j] = 0;
    }

    int getValue(std::string formula)
    {
        int plusIdx = formula.find('+');
        std::string x = formula.substr(1, plusIdx - 1);
        std::string y = formula.substr(plusIdx + 1);
        return getFormulaValue(x) + getFormulaValue(y);
    }

private:
    std::vector<std::vector<int>> sheet;

    std::pair<int, int> getCellIndex(const std::string& cell)
    {
        int i = std::stoi(cell.substr(1)) - 1;
        int j = cell[0] - 'A';
        return {i, j};
    }

    int getFormulaValue(const std::string& formula)
    {
        if (std::isalpha(formula[0]))
        {
            auto [i, j] = getCellIndex(formula);
            return sheet[i][j];
        }
        else
        {
            return std::stoi(formula);
        }
    }
};

int main()
{
    Spreadsheet spreadsheet(458);
    logObj(spreadsheet.getValue("=O126+10272"));

//    logObj(spreadsheet.getValue("=5+7"));
//    spreadsheet.setCell("A1", 10);
//    logObj(spreadsheet.getValue("=A1+6"));
//    spreadsheet.setCell("B2", 15);
//    logObj(spreadsheet.getValue("=A1+B2"));
//    spreadsheet.resetCell("A1");
//    logObj(spreadsheet.getValue("=A1+B2"));
    return 0;
}
