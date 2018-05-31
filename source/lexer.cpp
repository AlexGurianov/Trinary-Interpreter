// lexer.cpp

#include <map>
#include <unordered_set>

#include "myexceptions.h"
#include "lexer.h"

// Map of pre-created tokens for reserved words.
std::map<std::string, Token> reserved_words = { {"OUT", Token(OUT)}, {"WHILE", Token(WHILE)},
    {"DO", Token(DO)}, {"REPEAT", Token(REPEAT)}, {"IF", Token(IF)}, { "THEN", Token(THEN) },
    { "ELSE", Token(ELSE) }, { "END", Token(END) }};

// Set of first characters of reserved words.
std::unordered_set<char> reserved_word_starts = {'O', 'W', 'D', 'R', 'I', 'T', 'E'};

bool IsDelimiter(char c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v') {
        return true;
    } else {
        return false;
    }
}

bool IsLetter(char c) {
    if ('a' <= c && c <= 'z') {
        return true;
    } else {
        return false;
    }
}

bool IsCapitalLetter(char c) {
    if ('A' <= c && c <= 'Z') {
        return true;
    } else {
        return false;
    }
}

bool IsReservedWordStart(char c) {
    if (reserved_word_starts.find(c) != reserved_word_starts.end()) {
        return true;
    } else {
        return false;
    }
}

bool IsDigit(char c) {
    if (c == '0' || c == '+' || c == '-') {
        return true;
    }
    else {
        return false;
    }
}

void Lexer::SkipDelimiters() {
    while (IsDelimiter(current_char_)) {
        if (current_char_ == '\n') {
            current_line_++;
        }
        GetChar();
    }
}

std::string Lexer::Identifier() {
    std::string s(1, current_char_);
    GetChar();
    while (IsLetter(current_char_)) {
        s += current_char_;
        GetChar();
    }
    return s;
}

std::string Lexer::Number() {
    std::string s(1, current_char_);
    GetChar();
    while (IsDigit(current_char_)) {
        s += current_char_;
        GetChar();
    }
    return s;
}

std::string Lexer::ReservedWord() {
    std::string s(1, current_char_);
    GetChar();
    while (IsCapitalLetter(current_char_)) {
        s += current_char_;
        GetChar();
    }
    return s;
}

Token* Lexer::GetNextToken() {
    while (current_char_ != '\0') {
        if (IsDelimiter(current_char_)) {
            SkipDelimiters();
        }

        if (IsLetter(current_char_)) {
            std::string ident = Identifier();
            if (current_char_ == '0' || IsCapitalLetter(current_char_)) {
                throw invalidIdentifierError(ident.append(1, current_char_), current_line_);
            }
            return new IdentToken(IDENT, ident);
        }

        if (current_char_ == '0') {
            std::string number = Number();
            if (IsLetter(current_char_) || IsCapitalLetter(current_char_)) {
                throw invalidNumberError(number.append(1, current_char_), current_line_);
            }
            return new NumToken(NUM, TrinaryNumber(number));
        }

        if (IsReservedWordStart(current_char_)) {
            std::string reserved_word = ReservedWord();
            if (IsLetter(current_char_) || current_char_ == '0') {
                throw invalidReservedWordError(reserved_word.append(1, current_char_), current_line_, true);
            }
            auto token = reserved_words.find(reserved_word);
            if (token == reserved_words.end()) {
                throw invalidReservedWordError(reserved_word.append(1, current_char_), current_line_, false);
            }
            return &token->second;
        }

        if (current_char_ == '+') {
            GetChar();
            return new Token(PLUS);
        }

        if (current_char_ == '-') {
            GetChar();
            return new Token(MINUS);
        }

        if (current_char_ == '*') {
            GetChar();
            return new Token(MULT);
        }

        if (current_char_ == '(') {
            GetChar();
            return new Token(LBRACK);
        }

        if (current_char_ == ')') {
            GetChar();
            return new Token(RBRACK);
        }

        if (current_char_ == '&') {
            GetChar();
            return new Token(AND);
        }

        if (current_char_ == '|') {
            GetChar();
            return new Token(OR);
        }

        if (current_char_ == '~') {
            GetChar();
            return new Token(NOT);
        }

        if (current_char_ == '=') {
            GetChar();
            return new Token(EQ);
        }

        if (current_char_ == '#') {
            GetChar();
            return new Token(NOTEQ);
        }

        if (current_char_ == '<' && CheckNextChar() == '=') {
            GetChar();
            GetChar();
            return new Token(LESSEQ);
        }

        if (current_char_ == '>' && CheckNextChar() == '=') {
            GetChar();
            GetChar();
            return new Token(GREATEREQ);
        }

        if (current_char_ == '<') {
            GetChar();
            return new Token(LESS);
        }

        if (current_char_ == '>') {
            GetChar();
            return new Token(GREATER);
        }

        if (current_char_ == ':' && CheckNextChar() == '=') {
            GetChar();
            GetChar();
            return new Token(ASSIGN);
        }

        if (current_char_ == ';') {
            GetChar();
            return new Token(SEMI);
        }

        if (current_char_ == '\0') {
            return new Token(EOPROG);
        }

        throw forbiddenCharError(current_char_, current_line_);
    }
    return new Token(EOPROG);
}

std::string GetTokenTypeName(TokenType token_type) {
    switch (token_type) {
        case IDENT: return "identifier";
            break;
        case NUM: return "operand";
            break;
        case LBRACK: return "(";
            break;
        case RBRACK: return ")";
            break;
        case SEMI: return ";";
            break;
        case DO: return "DO";
            break;
        case REPEAT: return "REPEAT";
            break;
        case THEN: return "THEN";
            break;
        case ELSE: return "ELSE";
            break;
        case END: return "END";
            break;
        case ASSIGN: return ":=";
            break;
        case EOPROG: return "End of program";
            break;
        default: return "Something else";
    }
}