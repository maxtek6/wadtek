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
              << line_break << std::endl
              << "| " << std::setw(15) << std::left << "name" 
              << std::setw(14) << std::left << "size" 
              << "|" << std::endl
              << line_break << std::endl;
}

static void print_lumps(const wadtek::file &file)
{
    for (const auto &lump : file)
    {
        std::cout << "| " << std::setw(15) << std::left << lump.name() 
                  << std::setw(14) << std::left << lump.size() 
                  << "|" << std::endl;
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