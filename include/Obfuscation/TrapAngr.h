#include "llvm/Transforms/Utils/Local.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

namespace llvm {

class TrapAngr : public FunctionPass {
public:
    static char ID;
    bool enable;

    TrapAngr(bool enable) : FunctionPass(ID) { this->enable = enable; }

    bool runOnFunction(Function &F);

    void substitute(Instruction *I, int i);
};

FunctionPass *createTrapAngrPass(bool enable);

#if LLVM_VERSION_MAJOR >= 13
class TrapAngrPass : public PassInfoMixin<TrapAngrPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }
};
#endif
} // namespace llvm