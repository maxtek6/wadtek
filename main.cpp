#include <wadtek.hpp>

#include <iostream>

static void dumpwad_main(const std::string& path)
{
    wadtek::file file(path);
    std::cerr << "WAD file: " << file.identification() << std::endl;
    std::for_each(file.begin(), file.end(), [](const wadtek::lump& lump)
    {
        std::cout << lump.name() << " (" << lump.size() << " bytes)" << std::endl;
    });
}

int main(int argc, char** argv) 
{
    if (argc > 1)
    {
        dumpwad_main(argv[1]);
    }
    else
    {
        std::cerr << "usage: dumpwad <path>" << std::endl;
    }
    return 0;
}