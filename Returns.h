#pragma once

#include <llvm/Support/raw_os_ostream.h>
#include <llvm/IR/Instructions.h>

namespace clu {
  
void writeReturn(llvm::raw_ostream& out, llvm::ReturnInst& inst);

} // namespace clu
