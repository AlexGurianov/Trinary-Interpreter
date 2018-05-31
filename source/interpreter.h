// interpreter.h
// Purpose: Interpreter calls the parser to conctruct absract syntax tree (AST)
// and traverses it visiting the nodes.

#ifndef TRINARYINTERPRETER_INTERPRETER_H_
#define TRINARYINTERPRETER_INTERPRETER_H_

#include <map>

#include "trinarynumber.h"


// Forward declarations to avoid circular dependencies.

class Parser;

struct ProgramEntryNode;
struct UnaryOpNode;
struct BinaryOpNode;
struct IdentifierNode;
struct NumNode;
struct AssignNode;
struct OUTNode;
struct CompoundNode;
struct ConditionNode;
struct LoopNode;

class Interpreter {
    Parser *parser_;
    
    // The map stores the global variables defined in the code.
    std::map<std::string, TrinaryNumber> variables_;
public:
    Interpreter(Parser *parser) : parser_(parser) {}

    // Call the parser to construct AST and starts interpreting. Prints the error if encountered.
    void Interpret();

    // Visit of the node returns the result as trinary numbr or 0.

    TrinaryNumber Visit(ProgramEntryNode*);
    TrinaryNumber Visit(UnaryOpNode*);
    TrinaryNumber Visit(BinaryOpNode*);
    TrinaryNumber Visit(IdentifierNode*);
    TrinaryNumber Visit(NumNode*);
    TrinaryNumber Visit(AssignNode*);
    TrinaryNumber Visit(OUTNode*);
    TrinaryNumber Visit(CompoundNode*);
    TrinaryNumber Visit(ConditionNode*);
    TrinaryNumber Visit(LoopNode*);
};

#endif