#ifndef BYTES_HPP
#define BYTES_HPP

#include <cstdint>

#include <algorithm>
#include <string>

namespace wadtek
{
    enum class byte_order
    {
        little_endian,
        big_endian,
        undefined
    };

    constexpr byte_order host_byte_order()
    {
        union
        {
            uint32_t value;
            uint8_t c[4];
        } test = {1};
        return (test.c[0] == 1) ? byte_order::little_endian : (test.c[3] == 1) ? byte_order::big_endian
                                                                               : byte_order::undefined;
    }

    template <class IntType, byte_order ByteOrder = host_byte_order()> IntType read_int(uint8_t *data)
    {
        IntType value = *reinterpret_cast<IntType *>(data);
        if constexpr (ByteOrder == byte_order::big_endian)
        {
            std::reverse(reinterpret_cast<uint8_t *>(&value), reinterpret_cast<uint8_t *>(&value) + sizeof(IntType));
        }
        return value;
    }

    // TODO: possibly add template for execution policy
    std::string read_string(uint8_t *data, size_t size)
    {
        std::string result;
        result.reserve(size);
        std::for_each(
            data, 
            data + size, 
            [&result](uint8_t c) 
            { 
                if(c != 0)
                {
                    result.push_back(static_cast<char>(c)); 
                }
            });
        return result;
    }
}

#endif