#ifndef BYTES_HPP
#define BYTES_HPP

#include <cstdint>

#include <algorithm>
#include <string>

namespace wadtek
{
    std::function<void(uint8_t*,size_t)> get_swap_func()
    {
        uint16_t test = 0x0102;
        uint8_t *test_ptr = reinterpret_cast<uint8_t *>(&test);
        std::function<void(uint8_t*,size_t)> swap_func;
        if (test_ptr[0] != 0x02)
        {
            swap_func = [](uint8_t *data, size_t size) {
                std::reverse(data, data + size);
            };
        }
        return swap_func;
    }
    

    template <class IntType>
    IntType read_int(const uint8_t *data)
    {
        static auto swap_func = get_swap_func();
        IntType value = *reinterpret_cast<const IntType *>(data);
        if(swap_func)
        {
            swap_func(reinterpret_cast<uint8_t *>(&value), sizeof(IntType));
        }
        return value;
    }

    // TODO: possibly add template for execution policy
    std::string read_string(const uint8_t *data, size_t size)
    {
        std::string result;
        result.reserve(size);
        uint8_t byte;
        for (size_t offset = 0; offset < size; ++offset)
        {
            byte = *(data + offset);
            if (byte != 0)
            {
                result.push_back(static_cast<char>(byte));
            }
        }
        return result;
    }
}

#endif