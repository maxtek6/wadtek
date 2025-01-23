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

#ifndef WADTEK_HPP
#define WADTEK_HPP

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace wadtek
{
    class lump
    {
    public:
        lump(const std::string& name, const uint8_t* data, size_t size);
        lump(std::string&& name, const uint8_t* data, size_t size);
        lump(const lump& other) = default;
        lump(lump&& other) noexcept = default;
        ~lump() = default;

        const std::string& name() const;
        const uint8_t* data() const;
        size_t size() const;
    private:
        static std::pair<const uint8_t*, size_t> make_buffer(const uint8_t* data, size_t size);
        std::string _name;
        std::pair<const uint8_t*, size_t> _buffer;
    };

    class file
    {
    public:
        using const_iterator = std::vector<lump>::const_iterator;
        file(const std::string& path);
        file(const file& other) = delete;
        file(file&& other) noexcept = default;
        ~file() = default;

        const std::string& identification() const;

        const lump *data() const;
        size_t size() const;

        const_iterator begin() const;
        const_iterator end() const;
    private:
        void read_header();
        void read_lumps();
        std::string _identification;
        const uint8_t* _first_lump;
        std::unique_ptr<void,std::function<void(void*)>> _handle;
        std::vector<lump> _lumps;
    };
}

#endif