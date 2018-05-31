// parser.cpp

#include <set>

#include "abstractsyntaxtree.h"
#include "lexer.h"
#include "myexceptions.h"
#include "parser.h"

// Types of tokens that are not used in AST nodes.
std::set<TokenType> skipped_tokens { SEMI, LBRACK, RBRACK, ASSIGN, EOPROG };

void Parser::Eat(TokenType token_type) {
    if (current_token_->type == token_type) {
        if (skipped_tokens.find(current_token_->type) != skipped_tokens.end()) {
            delete current_token_;
        }
        current_token_ = lexer_->GetNextToken();
    } else {
        throw syntaxError(GetTokenTypeName(token_type), GetCurrentLine());
    }
}

ASTNode* Parser::Program() {
    return new ProgramEntryNode(CompoundActions());
}

ASTNode* Parser::CompoundActions() {
    CompoundNode* node = new CompoundNode();
    node->operands_list.push_back(Action());
    while (current_token_->type == SEMI) {
        Eat(SEMI);
        node->operands_list.push_back(Action());
    }
    return node;
}

ASTNode* Parser::Action() {
    switch (current_token_->type) {
        case OUT: {
            return Output();
            break;
        }
        case IDENT: {
            return Assignment();
            break;
        }
        case IF: {
            return Condition();
            break;
        }
        case WHILE: {
            return Loop();
            break;
        }
        default: {
            throw syntaxError("Assignment / output / loop / condition", GetCurrentLine());
        }
    }
}

ASTNode* Parser::Condition() {
    Eat(IF);
    auto condition = Expression();
    Eat(THEN);
    auto if_body = CompoundActions();
    ASTNode* else_body = NULL;
    bool else_part = false;
    if (current_token_->type == ELSE) {
        Eat(ELSE);
        else_body = CompoundActions();
        else_part = true;
    }
    Eat(END);
    return new ConditionNode(condition, if_body, else_body, else_part);
}

ASTNode* Parser::Loop() {
    Eat(WHILE);
    auto condition = Expression();
    Eat(DO);
    auto body = CompoundActions();    
    Eat(REPEAT);
    return new LoopNode(condition, body);
}

ASTNode* Parser::Output() {
    Eat(OUT);
    Eat(LBRACK);
    auto node = Expression();
    Eat(RBRACK);
    return new OUTNode(node);
}

ASTNode* Parser::Assignment() {
    Token *left_side = current_token_;
    Eat(IDENT);
    Eat(ASSIGN);
    return new AssignNode(left_side, Expression());
}

ASTNode* Parser::Expression() {
    auto node = Sum();
    Token *token = current_token_;
    switch (token->type) {
        case EQ: case NOTEQ: case LESS: case LESSEQ: case GREATER: case GREATEREQ: {
            Eat(token->type);
            return new BinaryOpNode(token, node, Sum());
            break;
        }
    }
    return node;
}

ASTNode* Parser::Sum() {
    auto node = Summand();
    Token *token = current_token_;
    while (token->type == PLUS || token->type == MINUS || token->type == OR) {
        Eat(token->type);
        node = new BinaryOpNode(token, node, Summand());
        token = current_token_;
    }
    return node;
}

ASTNode* Parser::Summand() {
    auto node = Multiplier();
    Token *token = current_token_;
    while (token->type == MULT || token->type == AND) {
        Eat(token->type);
        node = new BinaryOpNode(token, node, Multiplier());
        token = current_token_;
    }
    return node;
}

ASTNode* Parser::Multiplier() {
    Token *token = current_token_;
    switch (token->type) {
        case IDENT: {
            Eat(IDENT);
            return new IdentifierNode(token);
            break;
        }
        case NUM: {
            Eat(NUM);
            return new NumNode(token);
            break;
        }
        case LBRACK: {
            Eat(LBRACK);
            auto node = Expression();
            Eat(RBRACK);
            return node;
            break;
        }
        case NOT: {
            Eat(NOT);
            return new UnaryOpNode(token, Multiplier());
            break;
        }
        default: {
            throw syntaxError("Identifier / Number / ( / ~", GetCurrentLine());
        }
    }
}

ASTNode* Parser::Parse() {
    auto node = Program();
    if (current_token_->type != EOPROG) {
        throw syntaxError("End of program expected", GetCurrentLine());
    }
    return node;
}