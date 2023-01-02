#include "llvm/Transforms/Utils/Local.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

#pragma once

namespace llvm {

class HelloWorld : public FunctionPass {
public:
    static char ID;
    bool enable;

    HelloWorld(bool enable) : FunctionPass(ID) { this->enable = enable; }

    bool runOnFunction(Function &F);
};

FunctionPass *createHelloWorldPass(bool enable);

#if LLVM_VERSION_MAJOR >= 13
class HelloWorldPass : public PassInfoMixin<HelloWorldPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }
};
#endif
} // namespace llvm