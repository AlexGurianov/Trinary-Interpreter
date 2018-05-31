// filereader.cpp

#include <fstream>
#include <sstream>
#include <string>

#include "filereader.h"
#include "myexceptions.h"

FileReader::FileReader(char* filename) {
    std::ifstream input(filename, std::ifstream::in);
    if (!input.is_open())
    {
        throw fileError();
    }
    std::stringstream sstr;
    sstr << input.rdbuf();
    str = sstr.str() + "\0";
}