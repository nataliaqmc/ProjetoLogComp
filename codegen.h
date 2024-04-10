#include <stack>
#include <../llvm-14/llvm/IR/Module.h>
#include <../llvm-14/llvm/IR/Function.h>
#include <../llvm-14/llvm/IR/Type.h>

#include <../llvm-14/llvm/IR/DerivedTypes.h>
#include <../llvm-14/llvm/IR/LLVMContext.h>
#include <../llvm-14/llvm/IR/PassManager.h>
#include <../llvm-14/llvm/IR/Instructions.h>
#include <../llvm-14/llvm/IR/Verifier.h>
#include <../llvm-14/llvm/IR/CallingConv.h>
#include <../llvm-14/llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <../llvm-14/llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>


using namespace llvm;

class Block;

class CodeGeBlock {
public:
    BasicBlock *block;
    std::list<std::string, Value*> locals;
};

class CodeGenContext {
    std::stack<CodeGeBlock *> blocks;
    Function *mainFunction;

public:
    Module *module;
    CodeGenContext() { module = new Module("main", getGlobalContext()); }
    
    void generateCode(Block& root);
    GenericValue runCode();
    std::list<std::string, Value*>& locals() { return blocks.top()->locals; }
    BasicBlock *currentBlock() { return blocks.top()->block; }
    void pushBlock(BasicBlock *block) { blocks.push(new CodeGeBlock()); blocks.top()->block = block; }
    void popBlock() { CodeGeBlock *top = blocks.top(); blocks.pop(); delete top; }
};