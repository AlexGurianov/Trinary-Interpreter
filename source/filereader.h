// filereader.h
// Purpose: Filereader class reads the contents of source code file
// to a string and returns characters by index.

#ifndef TRINARYINTERPRETER_FILEREADER_H_
#define TRINARYINTERPRETER_FILEREADER_H_

#include <string>

class FileReader {
    std::string str;

public:
    FileReader(char*);

    char GetChar(int pos) const {
        return str[pos];
    }

    int size() const {
        return static_cast<int>(str.size()) - 1;
    }
};

#endif