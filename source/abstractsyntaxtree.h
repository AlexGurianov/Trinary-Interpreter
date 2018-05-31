// abstractsyntaxtree.h
// Purpose: Different types of nodes in abstract syntax tree.

#ifndef TRINARYINTERPRETER_ABSTRACTSYNTAXTREE_H_
#define TRINARYINTERPRETER_ABSTRACTSYNTAXTREE_H_

#include <vector>
#include <iostream>

#include "interpreter.h"
#include "lexer.h"
#include "myexceptions.h"

// Abstract base class for AST Node.
struct ASTNode {
    Token *token;
    std::vector<ASTNode*> operands_list;
    ASTNode(Token *t) : token(t) {}
    virtual TrinaryNumber AcceptInterpreter(Interpreter *inter) = 0;

    ~ASTNode() {
        delete token;
        for (std::vector<ASTNode*>::iterator it = operands_list.begin(); it != operands_list.end(); ++it) {
            delete (*it);
        }
        operands_list.clear();
    }
};

struct BinaryOpNode : ASTNode {
    BinaryOpNode(Token *t, ASTNode *l, ASTNode *r) : ASTNode(t) {
        operands_list.push_back(l);
        operands_list.push_back(r);
    }
    
    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct ProgramEntryNode : ASTNode {
    ProgramEntryNode(ASTNode *program) : ASTNode(NULL) {
        operands_list.push_back(program);
    }

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct UnaryOpNode : ASTNode {
    UnaryOpNode(Token *t, ASTNode *operand) : ASTNode(t) {
        operands_list.push_back(operand);
    }

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct IdentifierNode : ASTNode {
    IdentifierNode(Token *t) : ASTNode(t) {}

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct NumNode : ASTNode {
    NumNode(Token *t) : ASTNode(t) {}

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct AssignNode : ASTNode {
    AssignNode(Token* t, ASTNode *operand) : ASTNode(t) {
        operands_list.push_back(operand);
    }

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct OUTNode : ASTNode {
    OUTNode(ASTNode *operand) : ASTNode(NULL) {
        operands_list.push_back(operand);
    }

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct CompoundNode : ASTNode {
    CompoundNode() : ASTNode(NULL) {}

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct ConditionNode : ASTNode {
    ConditionNode(ASTNode *cond, ASTNode *if_body, ASTNode *else_body, bool is_else) : ASTNode(NULL) {
        operands_list.push_back(cond);
        operands_list.push_back(if_body);
        if (is_else) {
            operands_list.push_back(else_body);
        }
    }

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

struct LoopNode : ASTNode {
    LoopNode(ASTNode *condition, ASTNode *body) : ASTNode(NULL) {
        operands_list.push_back(condition);
        operands_list.push_back(body);
    }

    TrinaryNumber AcceptInterpreter(Interpreter* interpreter) override {
        return interpreter->Visit(this);
    }
};

#endif