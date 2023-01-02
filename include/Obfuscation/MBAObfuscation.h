#include "llvm/Transforms/Utils/Local.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

#pragma once

namespace llvm {

class MBAObfuscation : public FunctionPass {
public:
    static char ID;
    bool enable;

    MBAObfuscation(bool enable) : FunctionPass(ID) { this->enable = enable; }

    bool runOnFunction(Function &F);

    void substituteConstant(Instruction *I, int i);

    void substitute(BinaryOperator *BI);

    // 替换 Add 指令
    Value *substituteAdd(BinaryOperator *BI);

    // 替换 Sub 指令
    Value *substituteSub(BinaryOperator *BI);

    // 替换 And 指令
    Value *substituteAnd(BinaryOperator *BI);

    // 替换 Or 指令
    Value *substituteOr(BinaryOperator *BI);

    // 替换 Xor 指令
    Value *substituteXor(BinaryOperator *BI);
};

FunctionPass *createMBAObfuscationPass(bool enable);

#if LLVM_VERSION_MAJOR >= 13
class MBAObfuscationPass : public PassInfoMixin<MBAObfuscationPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }
};
#endif
} // namespace llvm