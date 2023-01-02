﻿#include "llvm/Transforms/Utils/Local.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

namespace llvm {
class RandomControlFlow : public FunctionPass {
public:
    static char ID;
    bool enable;

    RandomControlFlow(bool enable) : FunctionPass(ID) { this->enable = enable; }

    bool runOnFunction(Function &F);

    // 创建一组等效于 origVar 的指令
    Value *alterVal(Value *origVar, BasicBlock *insertAfter);

    void insertRandomBranch(Value *randVar, BasicBlock *ifTrue,
                            BasicBlock *ifFalse, BasicBlock *insertAfter);

    // 以基本块为单位进行随机控制流混淆
    bool randcf(BasicBlock *BB);
};

FunctionPass *createRandomControlFlow(bool enable);

#if LLVM_VERSION_MAJOR >= 13
class RandomControlFlowPass : public PassInfoMixin<RandomControlFlowPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }
};
#endif
} // namespace llvm