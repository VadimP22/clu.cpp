#pragma once

#include "llvm/Support/raw_ostream.h"
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/SourceMgr.h>

namespace clu {
    
class LuaWriter {
public:
    
    void writeModule(llvm::raw_ostream&, llvm::Module&);
    void debugPrintModule(llvm::raw_ostream&, llvm::Module&);

private:
    void writeFunction(llvm::raw_ostream&, llvm::Function&);
    void writeBasicBlock(llvm::raw_ostream&, llvm::BasicBlock&);
    void writeInstruction(llvm::raw_ostream&, llvm::Instruction&);

    std::string out_file_path_;
};
    
} // namespace clu
