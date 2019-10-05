/// Author: github.com/MetGang

#pragma once
#include <cstdint>

namespace hash
{

using Hash_t = std::uint32_t;

template<typename InputIt>
constexpr Hash_t fnv1a_32(InputIt begin)
{
    Hash_t value = 0x811C9DC5u;

    while (*begin)
    {
        value ^= *begin;
        value *= 0x1000193u;
        ++begin;
    }

    return value;
}

}


