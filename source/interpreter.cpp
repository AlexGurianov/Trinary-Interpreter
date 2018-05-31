// interpreter.cpp

#include <iostream>

#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include "trinarynumber.h"

void Interpreter::Interpret() {
    ASTNode* root = NULL;
    try {
        root = parser_->Parse();
        root->AcceptInterpreter(this);
        delete root;
    }
    catch (std::exception& ex) {
        if (root != NULL) {
            delete root;
        }
        std::cerr << "Error: " << ex.what() << "\n";
    }
}

TrinaryNumber Interpreter::Visit(ProgramEntryNode *node) {
    return node->operands_list[0]->AcceptInterpreter(this);
}

TrinaryNumber Interpreter::Visit(UnaryOpNode *node) {
    switch (node->token->type) {
        case NOT: {
            return ~node->operands_list[0]->AcceptInterpreter(this);
            break;
        }
        default: {
            return TrinaryNumber(0);
            break;
        }        
    }
}

TrinaryNumber Interpreter::Visit(BinaryOpNode *node) {
    switch (node->token->type) {
        case PLUS: {
            return node->operands_list[0]->AcceptInterpreter(this) + 
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case MINUS: {
            return node->operands_list[0]->AcceptInterpreter(this) -
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case MULT: {
            return node->operands_list[0]->AcceptInterpreter(this) *
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case AND: {
            return node->operands_list[0]->AcceptInterpreter(this) &
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case OR: {
            return node->operands_list[0]->AcceptInterpreter(this) |
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case EQ: {
            return node->operands_list[0]->AcceptInterpreter(this) ==
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case NOTEQ: {
            return node->operands_list[0]->AcceptInterpreter(this) !=
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case LESS: {
            return node->operands_list[0]->AcceptInterpreter(this) <
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case LESSEQ: {
            return node->operands_list[0]->AcceptInterpreter(this) <=
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case GREATER: {
            return node->operands_list[0]->AcceptInterpreter(this) >
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        case GREATEREQ: {
            return node->operands_list[0]->AcceptInterpreter(this) >=
                node->operands_list[1]->AcceptInterpreter(this);
            break;
        }
        default: {
            return TrinaryNumber(0);
            break;
        }
    }
}

TrinaryNumber Interpreter::Visit(IdentifierNode *node) {
    auto identifier = variables_.find(node->token->GetIdentifierName());
    if (identifier == variables_.end()) {
        throw undefinedVariableError(node->token->GetIdentifierName());
    }
    return identifier->second;
}

TrinaryNumber Interpreter::Visit(NumNode *node) {
    return node->token->GetNumValue();
}

TrinaryNumber Interpreter::Visit(AssignNode *node) {
    auto identifier = variables_.find(node->token->GetIdentifierName());
    if (identifier == variables_.end()) {
        variables_.insert({ node->token->GetIdentifierName() , node->operands_list[0]->AcceptInterpreter(this) });
    } else {
        identifier->second = node->operands_list[0]->AcceptInterpreter(this);
    }
    return TrinaryNumber(0);
}

TrinaryNumber Interpreter::Visit(OUTNode *node) {
    std::cout << node->operands_list[0]->AcceptInterpreter(this).GetTrinary() << "\n";
    return TrinaryNumber(0);
}

TrinaryNumber Interpreter::Visit(CompoundNode *node) {
    for (std::vector<ASTNode*>::iterator it = node->operands_list.begin(); it != node->operands_list.end(); ++it) {
        (*it)->AcceptInterpreter(this);
    }
    return TrinaryNumber(0);
}

TrinaryNumber Interpreter::Visit(ConditionNode *node) {
    TrinaryNumber cond_value = node->operands_list[0]->AcceptInterpreter(this);
    if (cond_value.IsLogical()) {
        if (cond_value.GetDecimal() == 1) {
            node->operands_list[1]->AcceptInterpreter(this);
        }
        else if (node->operands_list.size() == 3) {
            node->operands_list[2]->AcceptInterpreter(this);
        }
    }
    return TrinaryNumber(0);
}

TrinaryNumber Interpreter::Visit(LoopNode *node) {
    TrinaryNumber cond_value = node->operands_list[0]->AcceptInterpreter(this);
    while (cond_value.IsLogical() && cond_value.GetDecimal() == 1) {
        node->operands_list[1]->AcceptInterpreter(this);
        cond_value = node->operands_list[0]->AcceptInterpreter(this);
    }
    return TrinaryNumber(0);
}