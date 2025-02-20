#include "Returns.h"

#include <llvm/IR/Constants.h>
#include <llvm/ADT/APInt.h>
#include <llvm/Support/Casting.h>

#include "Utils.h"

void clu::writeReturn(llvm::raw_ostream& out, llvm::ReturnInst& inst) {
    out << "return ";

    // TODO add other types
    if (isa<llvm::ConstantInt>(inst.getReturnValue())) {
        auto& const_int = static_cast<llvm::ConstantInt&>(*inst.getReturnValue());
        out << const_int.getValue() << "\n";
    }
    else {
        out << clu::valueName(*inst.getReturnValue()) << "\n";
    }
}
