#include <wadtek.hpp>

#include <iomanip>
#include <iostream>

static const std::string line_break("+------------------------------+");

static void print_header(const wadtek::file &file)
{
    std::cout << line_break << std::endl 
              << "| " << std::setw(15) << std::left << file.identification() 
              << file.size() << std::setw(10)  << std::left  << " lumps"
              << "|" << std::endl
              << "|" << std::setw(34) << std::right 
              << "|" << std::endl
              << "| " << std::setw(15) << std::left << "name" 
              << std::setw(15) << std::left << "size" 
              << "|" << std::endl
              << line_break << std::endl;
}

static void print_lumps(const wadtek::file &file)
{
    for (const auto &lump : file)
    {
        std::cout << "| " << std::setw(15) << std::left << lump.name() 
                  << std::setw(15) << std::left << lump.size() 
                  << std::setw(3) << std::right << "|" 
                  << std::endl;
    }
    std::cout << line_break << std::endl;
}

static void dumpwad_main(const std::string &path)
{
    wadtek::file file(path);
    print_header(file);
    print_lumps(file);
}

int main(int argc, char **argv)
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