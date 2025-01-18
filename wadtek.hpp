#ifndef WADTEK_HPP
#define WADTEK_HPP

#include <algorithm>
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
        const_iterator begin() const;
        const_iterator end() const;
    private:
        std::string _identification;
        std::unique_ptr<void> _handle;
        std::vector<lump> _lumps;
    };
}

#endif