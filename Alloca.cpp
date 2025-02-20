#include "Alloca.h"

#include "Utils.h"

void clu::writeAlloca(llvm::raw_ostream& out, llvm::AllocaInst& inst) {
    if (inst.getAllocatedType()->isIntegerTy()) {
        out << "local " << clu::valueName(inst) << "\n";
    } 
}
