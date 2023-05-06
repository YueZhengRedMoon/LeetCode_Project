//
// Created by Kirie on 2023/5/4.
//

#ifndef __LEET_CODE_PROJECT_ALGORITHM_H
#define __LEET_CODE_PROJECT_ALGORITHM_H
#include <functional>
#include <iostream>

namespace kirie
{
    /** 在区间[0, n)根据可调用对象comp找到第一个大于或大于等于target的数的索引，传入comp的参数是区间的中点mid，
     *  comp应该具有如下形式：
     *  return nums[mid] > target;  // 在nums[0:n)中找到第一个(最小的)大于target的数，返回其索引
     *  return nums[mid] >= target; // 在nums[0:n)中找到第一个(最小的)大于等于target的数，返回其索引
     *  */
    int minGreaterEqual(int n, std::function<bool(int)> comp)
    {
        int left = 0, right = n;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            // nums[mid] >= target
            // nums[mid] > target
            if (comp(mid))
            {
                right = mid;
            }
            // nums[mid] < target
            // nums[mid] <= target
            else
            {
                // nums[mid] < target --> nums[mid + 1]可能>=target
                // nums[mid] <= target --> nums[mid + 1]可能>target
                left = mid + 1;
            }
        }
        return left;
    }

    /** 在区间[0, n)根据可调用对象comp找到最后一个小于或小于等于target的数的索引，传入comp的参数是区间的中点mid，
     *  comp应该具有如下形式：
     *  return nums[mid] < target;  // 在nums[0:n)中找到第一个(最大的)小于target的数，返回其索引
     *  return nums[mid] <= target; // 在nums[0:n)中找到第一个(最大的)小于等于target的数，返回其索引
     *  */
    int maxLessEqual(int n, std::function<bool(int)> comp)
    {
        int left = 0, right = n;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            // nums[mid] <= target
            // nums[mid] < target
            if (comp(mid))
            {
                left = mid + 1;
            }
            // nums[mid] > target
            // nums[mid] >= target
            else
            {
                right = mid;
            }
        }
        return left - 1;
    }

    template <typename T>
    T max(const T& t)
    {
        return t;
    }

    template <typename T, typename... Args>
    T max(const T& t, const Args&... args)
    {
        return std::max(t, max(args...));
    }

    template <typename T>
    T min(const T& t)
    {
        return t;
    }

    template <typename T, typename... Args>
    T min(const T& t, const Args&... args)
    {
        return std::min(t, min(args...));
    }
}

#endif //__LEET_CODE_PROJECT_ALGORITHM_H
