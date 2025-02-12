#include "clu.h"

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

int main(int argc, const char ** argv) {
    // using namespace llvm;

    if (argc == 1) {
        llvm::errs() << "Path to file expected\n";
        return 1;
    }
    
    llvm::LLVMContext context{};
    llvm::SMDiagnostic error{};
    clu::LuaWriter lua_writer{};
    
    std::unique_ptr<llvm::Module> module = parseIRFile(argv[1], error, context);
    if (!module) {
        error.print(argv[0], llvm::errs());
    }

    lua_writer.debugPrintModule(llvm::outs(), *module);    
    
    return 0;
}
