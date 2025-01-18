#include "wadtek.hpp"
#include "bytes.hpp"

#include <mio/mmap.hpp>

static std::unique_ptr<void, std::function<void(void *)>> make_handle(const std::string &path)
{
    return std::unique_ptr<void, std::function<void(void *)>>(
        new mio::basic_mmap<mio::access_mode::read, uint8_t>(path), 
        [](void *handle) { delete reinterpret_cast<mio::basic_mmap<mio::access_mode::read, uint8_t> *>(handle); });
}

static mio::basic_mmap<mio::access_mode::read, uint8_t> *get_handle(std::unique_ptr<void, std::function<void(void *)>> &handle)
{
    return reinterpret_cast<mio::basic_mmap<mio::access_mode::read, uint8_t> *>(handle.get());
}

std::pair<const uint8_t *, size_t> wadtek::lump::make_buffer(const uint8_t *data, size_t size)
{
    std::pair<const uint8_t *, size_t> buffer(nullptr, 0);
    if (data && size > 0)
    {
        buffer.first = data;
        buffer.second = size;
    }
    return buffer;
}

wadtek::lump::lump(const std::string &name, const uint8_t *data, size_t size)
    : _name(name), _buffer(make_buffer(data, size))
{
}

wadtek::lump::lump(std::string &&name, const uint8_t *data, size_t size)
    : _name(std::move(name)), _buffer(make_buffer(data, size))
{
}

const std::string &wadtek::lump::name() const
{
    return _name;
}

const uint8_t *wadtek::lump::data() const
{
    return _buffer.first;
}

size_t wadtek::lump::size() const
{
    return _buffer.second;
}

wadtek::file::file(const std::string &path)
    : _handle(make_handle(path))
{
    read_header();
    read_lumps();
}

void wadtek::file::read_header()
{
    const uint8_t *data = get_handle(_handle)->data();
    _identification = wadtek::read_string(data, 4);
    const int32_t num_lumps = wadtek::read_int<int32_t>(data + 4);
    const int32_t dir_offset = wadtek::read_int<int32_t>(data + 8);
    _first_lump = data + static_cast<size_t>(dir_offset);
    _lumps.reserve(num_lumps);
}

void wadtek::file::read_lumps()
{
    const uint8_t *head = get_handle(_handle)->data();
    const uint8_t* marker = _first_lump;
    while(_lumps.size() < _lumps.capacity())
    {
        int32_t file_pos;
        int32_t size;
        std::string name;
        file_pos = read_int<int32_t>(marker);
        marker += 4;
        size = read_int<int32_t>(marker);
        marker += 4;
        name = read_string(marker, 8);
        marker += 8;
        _lumps.emplace_back(name, head + static_cast<size_t>(file_pos), static_cast<size_t>(size));
    }
}

const std::string &wadtek::file::identification() const
{
    return _identification;
}

wadtek::file::const_iterator wadtek::file::begin() const
{
    return _lumps.begin();
}

wadtek::file::const_iterator wadtek::file::end() const
{
    return _lumps.end();
}