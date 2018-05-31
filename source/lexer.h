// leher.h
// Purpose: Lexer class tokenizes the source code and sequentially returns read tokens to the parser.

#ifndef TRINARYINTERPRETER_LEXER_H_
#define TRINARYINTERPRETER_LEXER_H_

#include <string>

#include "filereader.h"
#include "myexceptions.h"
#include "trinarynumber.h"

enum TokenType {
    IDENT, NUM, SEMI, OUT, LBRACK, RBRACK, IF, THEN, ELSE, END, WHILE, DO, REPEAT, ASSIGN, PLUS, MINUS,
    MULT, EQ, LESS, GREATER, LESSEQ, GREATEREQ, NOTEQ, OR, AND, NOT, EOPROG
};

// Base token class.
// When used for literals, contains just the token type. Other members are included for polymorphism.
struct Token {
    TokenType type;
    Token(TokenType t) : type(t), ident_value(""), num_value(0) {}
    Token(TokenType t, std::string s, TrinaryNumber num) : type(t), ident_value(s), num_value(num) {}

    virtual std::string GetIdentifierName() {
        throw noSuchFieldError();
    }

    virtual TrinaryNumber GetNumValue() {
        throw noSuchFieldError();
    }

protected:
    std::string ident_value;
    TrinaryNumber num_value;
};

// Identifier token class, contains token type and identifier name.
struct IdentToken : public Token {    
    IdentToken(TokenType t, std::string val) : Token(t, val, TrinaryNumber(0)) {}

    std::string GetIdentifierName() override {
        return ident_value;
    }
};

// Number token class, contains token type and trinary number.
struct NumToken : public Token {
    NumToken(TokenType t, TrinaryNumber num) : Token(t, "", num) {}

    TrinaryNumber GetNumValue() override{
        return num_value;
    }
};


// Lexer class reads the source code one character at a time and recognizes tokens. Throws errors when it is impossible.
class Lexer {
    FileReader *filereader_;
    int current_pos_, current_line_;
    char current_char_;

    void GetChar() {
        current_char_ = filereader_->GetChar(current_pos_);
        current_pos_++;
    }

    char CheckNextChar() {
        return filereader_->GetChar(current_pos_);
    }

    void SkipDelimiters();

    // Reads identifier name.
    std::string Identifier();

    // Reads trinary number string representation.
    std::string Number();

    // Reads reserved word.
    std::string ReservedWord();

public:
    Lexer(FileReader* f_r) : filereader_(f_r), current_pos_(0), current_line_(1) {
        GetChar();
    }

    Token* GetNextToken();

    int GetCurrentLine() {
        return current_line_;
    }
};


// Returns string representation of token type for error messages.
std::string GetTokenTypeName(TokenType);

#endif