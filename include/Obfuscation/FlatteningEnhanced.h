#ifndef LLVM_FLATTENING_ENHANCED_H
#define LLVM_FLATTENING_ENHANCED_H

#include "llvm/Transforms/Utils/Local.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include <list>
#include <vector>

namespace llvm {

class MyFlatten : public ModulePass {
public:
    static char ID;
    bool enable;

    MyFlatten(bool enable) : ModulePass(ID) { this->enable = enable; }

    std::vector<BasicBlock *> *getBlocks(Function *function,
                                        std::vector<BasicBlock *> *lists);
    void getAnalysisUsage(AnalysisUsage &AU);

    Function *buildUpdateKeyFunc(Module *m);

    unsigned int getUniqueNumber(std::vector<unsigned int> *rand_list);

    void DoFlatten(Function *f, int seed, Function *updateFunc);

    bool runOnModule(Module &module);

};

ModulePass *createFlatteningEnhancedPass(bool enable);

#if LLVM_VERSION_MAJOR >= 13
class MyFlattenPass : public PassInfoMixin<MyFlattenPass> {
public:
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);
  static bool isRequired() { return true; }
};
#endif
} // namespace llvm

#endif // LLVM_FLATTENING_H
