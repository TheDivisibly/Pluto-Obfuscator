#ifndef LLVM_FLATTENING_H
#define LLVM_FLATTENING_H

#include "llvm/Transforms/Utils/Local.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

namespace llvm {

class Flattening : public FunctionPass {
public:
    static char ID;
    bool enable;

    Flattening(bool enable) : FunctionPass(ID) { this->enable = enable; }

    void flatten(Function &F);

    bool runOnFunction(Function &F);
};

FunctionPass *createFlatteningPass(bool enable);

#if LLVM_VERSION_MAJOR >= 13
class FlatteningPass : public PassInfoMixin<FlatteningPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }
};
#endif
} // namespace llvm

#endif // LLVM_FLATTENING_H