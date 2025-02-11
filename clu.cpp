#include "clu.h"
#include "llvm/Support/raw_ostream.h"

int main(int argc, const char ** argv) {
    using namespace llvm;

    if (argc == 1) {
        errs() << "Path to file expected\n";
        return 1;
    }
    
    LLVMContext context{};
    SMDiagnostic error{};
    
    std::unique_ptr<Module> module = parseIRFile(argv[1], error, context);
    if (!module) {
        error.print(argv[0], errs());
    }

    auto& functions = module->getFunctionList();
    for (auto itt = functions.begin(); itt != functions.end(); ++itt) {
        auto& current_function = *itt;
        outs() << "Function: " << current_function.getName() << "\n";
        
        auto& block = current_function.getEntryBlock();
        for (auto itt = block.begin(); itt != block.end(); ++itt) {
            auto& current_instruction = *itt;
            outs() << "    Instruction: " << current_instruction.getOpcodeName() << "\n";
        }
    }

    return 0;
}
