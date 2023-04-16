//
// Created by Kirie on 2023/4/17.
//

#ifndef __LEET_CODE_PROJECT_DEBUG_H
#define __LEET_CODE_PROJECT_DEBUG_H
#include <iostream>
#include <vector>
#include <algorithm>

namespace debug
{
    template<typename T>
    void printVector(std::vector<T> vector, char split = ' ')
    {
        for (const auto& value : vector)
        {
            std::cout << value << split;
        }
        std::cout << std::endl;
    }

}
#endif //__LEET_CODE_PROJECT_DEBUG_H
