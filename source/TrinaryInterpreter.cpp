// TrinaryInterpreter.cpp
// Application entry points. Gets file with source code and runs the interpreter. 

#include <iostream>

#include "filereader.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[])
{   
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " source_file_path\n";
            return 1;
        }
        else {
            FileReader file_reader(argv[1]);
            Lexer lexer(&file_reader);
            Parser parser(&lexer);
            Interpreter interpreter(&parser);
            interpreter.Interpret();
            return 0;
        }
    }
    catch (std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }
}

