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
    : _handle(new mio::basic_mmap<mio::access_mode::read, uint8_t>(path))
{
    size_t offset = 0;
    uint32_t lump_count = 0;
    uint32_t lump_offset = 0;
    const uint8_t *data = get_handle(_handle)->data();
    const uint8_t *lump_marker;
    _identification = wadtek::read_string(data, 4);
    offset += 4;
    lump_count = wadtek::read_int<uint32_t>(data + offset);
    offset += 4;
    lump_offset = wadtek::read_int<uint32_t>(data + offset);
    lump_marker = data + lump_offset;
    _lumps.reserve(lump_count);
    while(_lumps.size() < _lumps.capacity())
    {
        offset = wadtek::read_int<uint32_t>(lump_marker + 8);
        size_t size = wadtek::read_int<uint32_t>(lump_marker + 12);
        std::string name = wadtek::read_string(lump_marker, 8);
        _lumps.emplace_back(name, data + offset, size);
        lump_marker += 16;
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