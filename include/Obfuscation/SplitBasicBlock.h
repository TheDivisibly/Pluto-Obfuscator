#ifndef LLVM_SPLIT_BASIC_BLOCK_H
#define LLVM_SPLIT_BASIC_BLOCK_H

#include "llvm/Transforms/Utils/Local.h"
#include <llvm/IR/Function.h>
#include "llvm/Pass.h"

namespace llvm {
class SplitBasicBlock : public FunctionPass {
public:
  static char ID;

  SplitBasicBlock() : FunctionPass(ID) {}

  bool runOnFunction(Function &F);

  // 对单个基本块执行分裂操作
  void split(BasicBlock *BB);

  // 判断一个基本块中是否包含 PHI指令(PHINode)
  bool containsPHI(BasicBlock *BB);
};

FunctionPass *createSplitBasicBlockPass();

#if LLVM_VERSION_MAJOR >= 13
class SplitBasicBlockPass : public PassInfoMixin<SplitBasicBlockPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }
};
#endif
} // namespace llvm

#endif // LLVM_SPLIT_BASIC_BLOCK_H