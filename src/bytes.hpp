#ifndef BYTES_HPP
#define BYTES_HPP

#include <cstdint>

#include <algorithm>
#include <string>

/*
 * Copyright 2025 Maxtek Consulting
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
                // possible bug here, I got a segfault when running on LE
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