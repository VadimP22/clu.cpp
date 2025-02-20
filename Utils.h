#pragma once

#include <llvm/IR/Value.h>

namespace clu {
  
std::string valueName(llvm::Value& value);
std::string toValidName(llvm::StringRef str);

} // namespace clu
