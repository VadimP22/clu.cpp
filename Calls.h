#pragma once

#include <llvm/Support/raw_os_ostream.h>
#include <llvm/IR/Instructions.h>

namespace clu {
  
void writeCall(llvm::raw_ostream& out, llvm::CallInst& inst);

} // namespace clu
 
