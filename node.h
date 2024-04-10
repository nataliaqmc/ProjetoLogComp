#include <iostream>
#include <vector>
#include <../llvm-14/llvm/IR/Value.h>

class CodeGenContext;

class Node {
public:
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) { return nullptr; }
};

class Expression : public Node {
};

class Statement : public Node {
};

class Integer : public Expression {
public:
    long long value;
    Integer(long long value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Double : public Expression {
public:
    double value;
    Double(double value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Identifier : public Expression {
public:
    std::string name;
    Identifier(const std::string& name) : name(name) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class MethodCall : public Expression {
public:
    const Identifier& id;
    std::vector<Expression*> arguments;
    MethodCall(const Identifier& id, std::vector<Expression*>& arguments) :
        id(id), arguments(arguments) { }
    MethodCall(const Identifier& id) : id(id) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class BinaryOperator : public Expression {
public:
    int op;
    Expression& lhs;
    Expression& rhs;
    BinaryOperator(Expression& lhs, int op, Expression& rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Assignment : public Expression {
public:
    Identifier& lhs;
    Expression& rhs;
    Assignment(Identifier& lhs, Expression& rhs) : 
        lhs(lhs), rhs(rhs) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Block : public Expression {
public:
    std::vector<Statement*> statements;
    Block() { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ExpressionStatement : public Statement {
public:
    Expression& expression;
    ExpressionStatement(Expression& expression) : 
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class VariableDeclaration : public Statement {
public:
    const Identifier& type;
    Identifier& id;
    Expression *assignmentExpr;
    VariableDeclaration(const Identifier& type, Identifier& id) :
        type(type), id(id), assignmentExpr(nullptr) { }
    VariableDeclaration(const Identifier& type, Identifier& id, Expression *assignmentExpr) :
        type(type), id(id), assignmentExpr(assignmentExpr) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class FunctionDeclaration : public Statement {
public:
    const Identifier& type;
    const Identifier& id;
    std::vector<VariableDeclaration*> arguments;
    Block& block;
    FunctionDeclaration(const Identifier& type, const Identifier& id, 
            const std::vector<VariableDeclaration*>& arguments, Block& block) :
        type(type), id(id), arguments(arguments), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class IfStatement : public Statement {
public:
    Expression& condition;
    Block& trueBlock;
    IfStatement(Expression& condition, Block& trueBlock) :
        condition(condition), trueBlock(trueBlock) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class IfNotStatement : public Statement {
public:
    Expression& condition;
    Block& trueBlock;
    Block& falseBlock;
    IfNotStatement(Expression& condition, Block& trueBlock, Block& falseBlock) :
        condition(condition), trueBlock(trueBlock), falseBlock(falseBlock) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class WhileLoop : public Statement {
public:
    Expression& condition;
    Block& loopBlock;
    WhileLoop(Expression& condition, Block& loopBlock) :
        condition(condition), loopBlock(loopBlock) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class PrintStatement : public Statement {
public:
    Expression& expression;
    PrintStatement(Expression& expression) :
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};
