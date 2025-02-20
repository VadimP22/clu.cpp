#pragma once

#include "llvm/IR/Instructions.h"
#include <llvm/Support/raw_ostream.h>
 
namespace clu {
    void writeAlloca(llvm::raw_ostream& out, llvm::AllocaInst& inst);
}
