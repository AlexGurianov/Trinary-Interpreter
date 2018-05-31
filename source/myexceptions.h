// myexceptions.h
// Purpose: Different types of exceptions with appropriate messages.

#ifndef TRINARYINTERPRETER_MYEXCEPTIONS_H_
#define TRINARYINTERPRETER_MYEXCEPTIONS_H_

#include <exception>
#include <string>

struct fileError : std::exception {
    const char* what() const noexcept {
        return "Cannot read file"; 
    }
};

struct forbiddenCharError : std::exception {
    char forbidden_char;
    int line_num;
    std::string message;

    forbiddenCharError(char c, int l_num): forbidden_char(c), line_num(l_num) {
        message = "Uknown character '";
        message.append(1, forbidden_char).append("' in line ").append(std::to_string(line_num));
    }

    const char* what() const noexcept {
        return message.c_str();
    }
};

struct invalidIdentifierError : std::exception {
    std::string identifier;
    int line_num;
    std::string message;

    invalidIdentifierError(std::string ident, int l_num) : identifier(ident), line_num(l_num) {
        message = "Forbidden identifier \"";
        message.append(identifier).append("...\" in line ").append(std::to_string(line_num));
    }

    const char* what() const noexcept {
        return message.c_str();
    }
};

struct invalidNumberError : std::exception {
    std::string number;
    int line_num;
    std::string message;

    invalidNumberError(std::string num, int l_num) : number(num), line_num(l_num) {
        message = "Invalid number \"";
        message.append(number).append("...\" in line ").append(std::to_string(line_num));
    }

    const char* what() const noexcept {
        return message.c_str();
    }
};

struct invalidReservedWordError : std::exception {
    std::string word;
    int line_num;
    bool no_space;
    std::string message;

    invalidReservedWordError(std::string w, int l_num, bool no_sp) : word(w), 
        line_num(l_num), no_space(no_sp) {
        message = "Invalid reserved word \"";
        message.append(word);
        if (no_space) {
            message.append("...\" in line ");
        }
        else {
            message.append(" in line ");
        }
        message.append(std::to_string(line_num));
    }

    const char* what() const noexcept {
        return message.c_str();
    }
};

struct syntaxError : std::exception {
    std::string tokenType;
    int line_num;
    std::string message;

    syntaxError(std::string tType, int l_num) : tokenType(tType), line_num(l_num) {
        message = tokenType;
        message.append(" expected in line ").append(std::to_string(line_num));
    }

    const char* what() const noexcept {        
        return message.c_str();
    }
};

struct notLogicalError : std::exception {
    std::string number;
    int line_num;
    std::string message;

    notLogicalError(std::string num) : number(num) {
        message = "Number \"";
        message.append(number).append("\" is not logical (0, +, -)");
    }

    const char* what() const noexcept {
        return message.c_str();
    }
};

struct noSuchFieldError : std::exception {
    const char* what() const noexcept {
        return "No such field in class";
    }
};

struct undefinedVariableError : std::exception {
    std::string identifier;
    std::string message;

    undefinedVariableError(std::string ident) : identifier(ident) {
        message = "Variable \"";
        message.append(identifier).append("\" undefined in line ");
    }

    const char* what() const noexcept {
        return message.c_str();
    }
};

#endif