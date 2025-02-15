#include "LuaWriter.h"

void clu::LuaWriter::debugPrintModule(llvm::raw_ostream& out, llvm::Module& module) {
    auto& functions = module.getFunctionList();
    
    llvm::outs() << "Module: " << module.getName() << "\n";
    
    for (auto itt = functions.begin(); itt != functions.end(); ++itt) {
        auto& current_function = *itt;
        llvm::outs() << "    Function: " << current_function.getName() << "\n";
        
        auto& block = current_function.getEntryBlock();
        for (auto itt = block.begin(); itt != block.end(); ++itt) {
            auto& current_instruction = *itt;
            llvm::outs() << "        Instruction: " << current_instruction.getOpcodeName() << "\n";
            llvm::outs() << "            Text: " << current_instruction << "\n";
        }
    }
}
