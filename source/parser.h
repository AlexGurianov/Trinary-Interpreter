// parser.h
// Purpose: Parser constructs absract syntax tree (AST) calling lexer to get tokens. 

#ifndef TRINARYINTERPRETER_PARSER_H_
#define TRINARYINTERPRETER_PARSER_H_

#include "abstractsyntaxtree.h"
#include "lexer.h"

// Parses the source code according to the defined grammar. Throws errors if syntax rules are violated.
class Parser {
    Lexer *lexer_;
    Token *current_token_;

    // If current token matches given token type, calls lexer and shifts
    // to the next token, throws error otherwise.
    void Eat(TokenType);

    // Functions to accordingly process different syntax structures. 

    ASTNode* Program();
    ASTNode* CompoundActions();
    ASTNode* Action();
    ASTNode* Assignment();
    ASTNode* Output();
    ASTNode* Condition();
    ASTNode* Loop();
    ASTNode* Expression();
    ASTNode* Sum();
    ASTNode* Summand();
    ASTNode* Multiplier();

public:
    Parser(Lexer *lexer) : lexer_(lexer), current_token_(lexer_->GetNextToken()) {}
    
    int GetCurrentLine() {
        return lexer_->GetCurrentLine();
    }

    // Constructs AST and returns its root.
    ASTNode* Parse();
};

#endif