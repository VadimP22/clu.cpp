#include "LuaWriter.h"

int main(int argc, const char ** argv) {

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
