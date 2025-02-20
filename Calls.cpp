#include "Calls.h"

#include "Utils.h"

void clu::writeCall(llvm::raw_ostream& out, llvm::CallInst& inst) {
    auto& called_function = *inst.getCalledFunction();

    out << clu::valueName(inst) << " = " << toValidName(called_function.getName());

    if (inst.arg_empty()) {
        out << "()\n";
        return;
    }
}




