#ifndef LLVM_GLOBALS_ENCRYPTION_H
#define LLVM_GLOBALS_ENCRYPTION_H

#include "llvm/Transforms/Utils/Local.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"

namespace llvm {

struct EncryptedGV {
    GlobalVariable *GV;
    uint64_t key;
    uint32_t len;
};

class GlobalsEncryption : public ModulePass {
public:
    static char ID;
    bool enable;

    GlobalsEncryption(bool enable) : ModulePass(ID) { this->enable = enable; }

    bool runOnModule(Module &M) override;

    void insertArrayDecryption(Module &M, EncryptedGV encGV);

    void insertIntDecryption(Module &M, EncryptedGV encGV);
};

ModulePass *createGlobalsEncryptionPass(bool enable);

#if LLVM_VERSION_MAJOR >= 13
class GlobalsEncryptionPass : public PassInfoMixin<GlobalsEncryptionPass> {
public:
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);
  static bool isRequired() { return true; }
};
#endif
} // namespace llvm

#endif // LLVM_GLOBALS_ENCRYPTION_H