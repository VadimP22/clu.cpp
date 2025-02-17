#include "LuaWriter.h"
#include "llvm/IR/Type.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constant.h>

#include <sstream>
#include <string>

void clu::LuaWriter::debugPrintModule(llvm::raw_ostream& out, llvm::Module& module) {
    auto& functions = module.getFunctionList();
    
    llvm::outs() << "Module: " << module.getName() << "\n";
    
    for (auto itt = functions.begin(); itt != functions.end(); ++itt) {
        auto& current_function = *itt;
        llvm::outs() << "    Function: " << current_function.getName() << "\n";
        
        // auto& block = current_function.getEntryBlock();
        //
        for (auto itt = current_function.begin(); itt != current_function.end(); ++itt) {
            auto& current_basic_block = *itt;
            llvm::outs() << "        BasicBlock: " << current_basic_block.getName() << "\n";
            
            for (auto itt = current_basic_block.begin(); itt != current_basic_block.end(); ++itt) {
                auto& current_instruction = *itt;
                llvm::outs() << "            Instruction: " << current_instruction.getOpcodeName() << "\n";
                llvm::outs() << "                Text: " << current_instruction << "\n";
            }
        }
        
    }
}

std::string toValidName(llvm::StringRef str) {
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
std::string generateName(llvm::Value& value) {
    std::stringstream result{};
    
    result << "val";
    result << &value;

    return result.str();
}

void clu::LuaWriter::writeModule(llvm::raw_ostream& out, llvm::Module& module) {
    auto& functions = module.getFunctionList();
       
    for (auto itt = functions.begin(); itt != functions.end(); ++itt) {
        auto& current_function = *itt;
       
        writeFunction(out, current_function);
    }
    
}

void writeFunctionHeader(llvm::raw_ostream& out, llvm::Function& function) {
    out << "function " << toValidName(function.getName());
    
    if (function.arg_empty()) {
        out << "()\n";
        return;
    }
    
    out << "(";
    for (auto itt = function.args().begin(); itt != function.args().end(); ++itt) {
        auto& current_arg = *itt;
        auto arg_index = current_arg.getArgNo();
        
        

        out << generateName(current_arg);
        if (itt != function.args().end() - 1)
            out << ", ";
    }

    out << ")\n";
}

void clu::LuaWriter::writeFunction(llvm::raw_ostream& out, llvm::Function& function) {
    writeFunctionHeader(out, function);

    for (auto itt = function.begin(); itt != function.end(); ++itt) {
       auto& current_basic_block = *itt; 
       writeBasicBlock(out, current_basic_block);
    }

    out << "end\n";
}

void clu::LuaWriter::writeBasicBlock(llvm::raw_ostream& out, llvm::BasicBlock& basic_block) {
    for (auto itt = basic_block.begin(); itt != basic_block.end(); ++itt) {
        auto& current_instrution = *itt;
        writeInstruction(out, current_instrution);
    }
}



void writeCall(llvm::raw_ostream& out, llvm::CallInst& inst) {
    auto& called_function = *inst.getCalledFunction();

    out << generateName(inst) << " = " << toValidName(called_function.getName());

    if (inst.arg_empty()) {
        out << "()\n";
        return;
    }
}

bool isNumberType(llvm::Type& type) {
    bool result = false;

    result = result || type.isIntegerTy();
    result = result || type.isFloatingPointTy();
    result = result || type.isDoubleTy();
    
    return result;
}

// TODO separate to writeReturnConstantFloat writeReturnConstantInt and simillar.
void writeReturnConstantNumber(llvm::raw_ostream& out, llvm::ReturnInst& inst) {
    auto& return_value = *inst.getReturnValue();
    auto& return_constant = static_cast<llvm::Constant&>(return_value);
    
    out << "return " << return_constant.getUniqueInteger() << "\n";
}

void writeReturn(llvm::raw_ostream& out, llvm::ReturnInst& inst) {
    auto& type = *inst.getReturnValue()->getType();

    if (isNumberType(type))
        writeReturnConstantNumber(out, inst);
}

void clu::LuaWriter::writeInstruction(llvm::raw_ostream& out, llvm::Instruction& instruction) {
    auto opcode = instruction.getOpcode();

    if (opcode == llvm::Instruction::Call) {
        auto& call_inst = static_cast<llvm::CallInst&>(instruction);
        writeCall(out, call_inst);
    } else if (opcode == llvm::Instruction::Ret) {
        auto& ret_inst = static_cast<llvm::ReturnInst&>(instruction);
        writeReturn(out, ret_inst);
    }
}
    
