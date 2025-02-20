#include "Utils.h"

#include <sstream>

std::string clu::valueName(llvm::Value& value) {
    std::stringstream result{};
    
    result << "val";
    result << &value;

    return result.str();
}

std::string clu::toValidName(llvm::StringRef str) {
    std::stringstream result{};

    for (auto itt = str.begin(); itt != str.end(); ++itt) {
        if (*itt == '?')
            result << 'q';
        else if (*itt == '@')
            result << 'a';
        else
            result << *itt;    
    }

    return result.str();
}
