//
// Created by Kirie on 2023/4/17.
//

#ifndef __LEET_CODE_PROJECT_DEBUG_H
#define __LEET_CODE_PROJECT_DEBUG_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

#define print(obj) std::cout << obj
#define println(obj) std::cout << obj << std::endl
#define logObj(obj) std::cout << #obj << " = " << obj << std::endl


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

    template<typename T>
    void printVector2D(std::vector<std::vector<T>> vector2D, char split = ' ', char endLine = '\n')
    {
        for (const auto &vector : vector2D)
        {
            for (const auto &value : vector)
            {
                std::cout << value << split;
            }
            std::cout << endLine;
        }
    }

    template<typename T>
    void printVector2D(std::vector<std::vector<T>> vector2D, const T& inf, char split = ' ')
    {
        for (const auto &vector : vector2D)
        {
            for (const auto &value : vector)
            {
                if (value == inf)
                {
                    std::cout << "inf" << split;
                }
                else
                {
                    std::cout << value << split;
                }

            }
            std::cout << std::endl;
        }
    }

    template<typename Iter>
    void printIterRange(Iter begin, Iter end, char split = ' ')
    {
        for (Iter it = begin; it != end; ++it)
        {
            std::cout << *it << split;
        }
        std::cout << std::endl;
    }

    template<int N>
    void printBinaryValue(unsigned int value)
    {
        std::bitset<N> bits(value);
        std::cout << bits.to_string() << std::endl;
    }
}
#endif //__LEET_CODE_PROJECT_DEBUG_H
