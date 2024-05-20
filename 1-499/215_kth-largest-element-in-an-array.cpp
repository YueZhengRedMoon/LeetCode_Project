#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        // 第k大等于第n-k小
        int n = nums.size();
        std::nth_element(nums.begin(), nums.begin() + n - k, nums.end());
        return nums[n - k];
    }
};

class Solution2
{
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        k = n - k;
        kthElement(nums, 0, n, k);
        return nums[k];
    }

private:
    // 将nums中第k小的元素放到nums[k]，使得所有的i>k的元素有nums[i]>nums[k]，所有的i<k的元素有nums[i]<nums[k]
    void kthElement(std::vector<int>& nums, int left, int right, int k)
    {
        if (left >= right || k >= right)
            return;

        int pivot = right - 1;  // 选择一个枢轴，使得所有比他小的元素都在它的左边，所有比它大的元素都在它的右边
        int l = left, r = right - 1;
        while (l < r)
        {
            // 找到第一个大于等于枢轴的元素，准备将其交换到枢轴的右边
            while (l < r && nums[l] < nums[pivot])
                ++l;

            // 找到第一个小于枢轴的元素，准备将其交换到枢轴的左边
            while (l < r && nums[r] >= nums[pivot])
                --r;

            // 交换两个元素到正确的位置
            if (l < r)
                std::swap(nums[l], nums[r]);
        }

        // 循环结束时l指向的是最小的>=nums[pivot]的元素，将其与枢轴交换
        std::swap(nums[l], nums[pivot]);

        // 枢轴元素正好是第k个元素，找到了第k小的元素
        if (l == k)
            return;
        // 枢轴元素第在k个元素的左边，在枢轴元素的右边继续寻找
        else if (l < k)
            kthElement(nums, l + 1, right, k);
        // 枢轴元素在第k个元素的右边，在枢轴元素的左边继续寻找
        else
            kthElement(nums, left, l, k);
    }
};

class Solution3
{
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        k = n - k;
        nth_element(nums.begin(), nums.begin() + k, nums.end());
        return nums[k];
    }

private:
    template<typename RandomIt>
    void nth_element(RandomIt first, RandomIt nth, RandomIt last)
    {
        if (first >= last || nth >= last)
            return;
        // 选择一个枢轴，使得所有比他小的元素都在它的左边，所有比它大的元素都在它的右边
        RandomIt pivot = std::prev(last);
        RandomIt left = first;
        RandomIt right =std::prev(last);
        while (left < right)
        {
            // 找到第一个大于等于枢轴的元素，准备将它交换到枢轴的右边
            while (left < right && *left < *pivot)
                ++left;
            // 找到第一个小于枢轴的元素，准备将它交换到枢轴的左边
            while (left < right && *right >= *pivot)
                --right;
            // 交换两个元素到正确的位置
            if (left < right)
                std::iter_swap(left, right);
        }
        // 循环结束时left指向的是最小的 >= pivot的元素，将其与枢轴交换
        std::iter_swap(left, pivot);
        // 枢轴元素正好是第n个元素，找到了第n小的元素
        if (left == nth)
            return;
            // 枢轴元素在第n个元素左边，在枢轴元素的右边继续寻找
        else if (left < nth)
            nth_element(left + 1, nth, last);
            // 枢轴元素在第n个元素的右边，在枢轴元素的左边继续寻找
        else
            nth_element(first, nth, left);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
