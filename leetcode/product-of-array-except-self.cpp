#include <iostream>
#include <vector>

std::vector<int> solve(std::vector<int> const& nums)
{
    std::vector<int> suffixProducts;
    suffixProducts.resize(nums.size());
    int suffixProduct = 1;
    for (int i = nums.size() - 1; i >= 0; --i)
    {
        suffixProducts[i] = suffixProduct;
        suffixProduct *= nums[i];
    }

    int prefixProduct = 1;
    for (int i = 0; i < nums.size(); ++i)
    {
        suffixProducts[i] = prefixProduct * suffixProducts[i];
        prefixProduct *= nums[i];
    }

    return suffixProducts;
}

int main()
{
    for (int const num : solve({1,2,3,4}))
    {
        std::cout << num << ",";
    }
    std::cout << "\n";
    for (int const num : solve({-1,1,0,-3,3}))
    {
        std::cout << num << ",";
    }
    std::cout << "\n";
}