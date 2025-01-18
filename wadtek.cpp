#include "wadtek.hpp"

#include <mmap.hpp>

static mio::basic_mmap_source<uint8_t>* get_handle(std::unique_ptr<void>& handle)
{
    return reinterpret_cast<mio::basic_mmap_source<uint8_t>*>(handle.get());
}

std::pair<const uint8_t*, size_t> wadtek::lump::make_buffer(const uint8_t* data, size_t size)
{
    std::pair<const uint8_t*, size_t> buffer(nullptr, 0);
    if (data && size > 0)
    {
        buffer.first = data;
        buffer.second = size;
    }
    return buffer;
}

wadtek::lump::lump(const std::string& name, const uint8_t* data, size_t size)
    : _name(name), _buffer(make_buffer(data, size))
{
}

wadtek::lump::lump(std::string&& name, const uint8_t* data, size_t size)
    : _name(std::move(name)), _buffer(make_buffer(data, size))
{
}

const std::string& wadtek::lump::name() const
{
    return _name;
}

const uint8_t* wadtek::lump::data() const
{
    return _buffer.first;
}

size_t wadtek::lump::size() const
{
    return _buffer.second;
}

wadtek::file::file(const std::string& path)
    : _handle(new mio::basic_mmap_source<uint8_t>(path))
{
    mio::basic_mmap_source<uint8_t>* data = get_handle(_handle);
}

const std::string& wadtek::file::identification() const
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