#include <chrono>
#include <cstring>
#include <exception>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::string encode(std::vector<std::string> const& strs)
{
    int const strCount = strs.size();
    int strsSize = 0;
    for (std::string const& str : strs)
    {
        strsSize += str.size();
    }

    std::string result;
    result.resize(sizeof(int) + strCount * sizeof(int) + strsSize);
    char* out = result.data();

    std::memcpy(out, &strCount, sizeof(int));
    out += sizeof(int);

    for (std::string const& str : strs)
    {
        int const size = str.size();
        std::memcpy(out, &size, sizeof(int));
        out += sizeof(int);
    }

    for (std::string const& str : strs)
    {
        std::memcpy(out, str.data(), str.size());
        out += str.size();
    }

    return result;
}

std::vector<std::string> decode(std::string const& str)
{
    char const* sizesSrc = str.data();
    int strCount;
    std::memcpy(&strCount, sizesSrc, sizeof(int));
    sizesSrc += sizeof(int);
    char const* strSrc = sizesSrc + strCount * sizeof(int);
    std::vector<std::string> result;
    for (int i = 0; i < strCount; ++i)
    {
        result.emplace_back();
        std::string& str = result.back();
        int size;
        std::memcpy(&size, sizesSrc, sizeof(int));
        str.resize(size);
        std::memcpy(str.data(), strSrc, size);
        sizesSrc += sizeof(int);
        strSrc += size;
    }
    return result;
}

auto generate_input (std::ranlux48& rng) -> std::vector<std::string>
{
    std::vector<std::string> result;
    for (int i = 0; i < 100; ++i)
    {
        std::uniform_int_distribution<int> lenghtDist(5, 100'000);
        std::uniform_int_distribution<int> charDist((int)'a', (int)'z');
        int const length = lenghtDist(rng);
        std::string str;
        str.resize(length);
        for (int j = 0; j < length; ++j)
        {
            str[j] = (char)charDist(rng);
        }
        result.emplace_back(std::move(str));
    }
    return result;
}

void test(int testCount)
{
    std::chrono::milliseconds total(0);
    std::ranlux48 rng(144);
    for (int i = 0; i < testCount; ++i)
    {
        std::vector<std::string> input = generate_input(rng);
        auto const start = std::chrono::high_resolution_clock::now();
        auto result = decode(encode(input));
        auto const end = std::chrono::high_resolution_clock::now();
        if (input != result)
        {
            std::cout << "missmatch for input i = " << i << "\n";
            std::terminate();
        }
        auto const elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "elapsed\t" << elapsed.count() << "ms\n";
        total += std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    }
    std::cout << "total\t" << total.count() << "ms\n";
}

int main()
{
    test(10);
}